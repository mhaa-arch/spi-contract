#ifndef MHAA_SPI_CONTROLLER_HPP
#define MHAA_SPI_CONTROLLER_HPP

#include <stdint.h>
#include <stddef.h>
#include <spi/types.hpp>

namespace mhaa
{
    namespace spi
    {
        /** @brief Exchanges words on a configured SPI peripheral. */
        class Controller
        {
        public:
            virtual ~Controller() = default;
            virtual Status configure(const Config &config) = 0;

            /** @brief Exchanges low-aligned words within one positive timeout budget. */
            virtual Result exchange(const Word *tx, Word *rx, size_t count,
                                    uint32_t timeout_ms) = 0;
        };
    }
}

#endif
