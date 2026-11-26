#include <spi/controller.hpp>

using namespace mhaa::spi;

class Incomplete final : public Controller
{
public:
    Result exchange(const Word *tx, Word *rx, size_t count, uint32_t timeout_ms) override;
};

int main()
{
    Incomplete implementation;
    (void)implementation;
}
