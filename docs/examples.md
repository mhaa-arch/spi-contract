# SPI Contract example

[The conformance program](../tests/conformance.cpp) pairs a simulated implementation with assertions at the Contract boundary. The fake accepts a 24-bit configuration and modifies the first word in an in-place buffer. It then reports a timeout with one completed word. The program checks the received prefix and confirms that the second word is untouched. This illustrates partial results without modeling clock edges.

## Implementation excerpt

This class is taken from the program. The linked source contains the test cases and any additional fixtures.

```cpp
#include <spi/controller.hpp>


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
```

## Build and run

From this repository root, with assertions enabled, compile the full program. A passing run exits with status 0 and prints no output. Use `conformance.exe` on Windows.

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude tests/conformance.cpp -o conformance
./conformance
```

To verify enforcement of the abstract interface, compile the two negative sources separately. The first should diagnose an abstract type and the second an incompatible override.

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude -fsyntax-only tests/missing_override.cpp
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude -fsyntax-only tests/wrong_override.cpp
```
