#ifndef MHAA_SPI_BYTE_EXCHANGE_HPP
#define MHAA_SPI_BYTE_EXCHANGE_HPP

#include <stddef.h>
#include <stdint.h>
#include <spi/controller.hpp>
#include <spi/types.hpp>

namespace mhaa
{
    namespace spi
    {
        /** @brief Exchanges packed byte buffers on the same controller in eight-bit mode. */
        class ByteExchange : public Controller
        {
        public:
            /** @brief Uses one finite budget. Only the completed receive prefix changes.
             *  @return Unsupported when the configured word width is not eight bits.
             */
            virtual Result exchange_bytes(const uint8_t *tx, uint8_t *rx, size_t count,
                                          uint32_t timeout_ms) = 0;
        };
    }
}

#endif
