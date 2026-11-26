#include <spi/controller.hpp>

using namespace mhaa::spi;

class WrongOverride final : public Controller
{
public:
    Status configure(const Config &config) const override;
};
