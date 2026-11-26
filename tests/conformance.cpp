#include <spi/controller.hpp>

#include <cassert>

using namespace mhaa::spi;

class Fake final : public Controller
{
public:
    Status configure(const Config &config) override
    {
        if (config.word_bits != 24)
        {
            return Status::Unsupported;
        }
        configured_ = true;
        return Status::Success;
    }

    Result exchange(const Word *tx, Word *rx, size_t count, uint32_t timeout_ms) override
    {
        if (!timeout_ms)
        {
            return {Status::InvalidArgument, 0};
        }
        if (!configured_)
        {
            return {Status::Busy, 0};
        }
        if (count == 0)
        {
            return {Status::Success, 0};
        }
        rx[0] = tx[0] ^ UINT32_C(0x800000);
        return {count == 1 ? Status::Success : Status::Timeout, 1};
    }

private:
    bool configured_ = false;
};

int main()
{
    Fake fake;
    Controller &controller = fake;
    assert(controller.configure({Mode::Mode3, BitOrder::MostSignificantFirst,
                                 Role::Controller, 1000000, 24}) == Status::Success);
    Word words[] = {0x12, 0xFC};
    const auto result = controller.exchange(words, words, 2, 10);
    assert(result.status == Status::Timeout && result.completed == 1);
    assert(words[0] == 0x800012 && words[1] == 0xFC);
}
