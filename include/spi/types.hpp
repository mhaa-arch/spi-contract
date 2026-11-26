#ifndef MHAA_SPI_TYPES_HPP
#define MHAA_SPI_TYPES_HPP

#include <stdint.h>
#include <stddef.h>

namespace mhaa
{
    namespace spi
    {
        enum class Mode
        {
            Mode0,
            Mode1,
            Mode2,
            Mode3
        };
        enum class BitOrder
        {
            MostSignificantFirst,
            LeastSignificantFirst
        };
        enum class Role
        {
            Controller,
            Target
        };
        using Word = uint32_t;

        struct Config
        {
            Mode mode;
            BitOrder bit_order;
            Role role;
            uint32_t frequency_hz;
            uint8_t word_bits;
        };

        enum class Status
        {
            Success,
            Busy,
            InvalidArgument,
            Unsupported,
            Timeout,
            Error
        };

        struct Result
        {
            Status status;
            size_t completed;
        };
    }
}

#endif
