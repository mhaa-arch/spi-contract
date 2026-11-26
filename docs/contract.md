# SPI contract

## Configure the link

[Controller](../include/spi/controller.hpp) accepts supported [Config](../include/spi/types.hpp) combinations. Clock mode and bit order must agree with the peer. A clock-generating controller requests positive nominal hertz. A target supplies zero because an external controller supplies the clock. The width is 1 to 32 bits. A word occupies the low configured bits of `Word`.

## Exchange and report progress

Provide transmit and receive arrays of at least the declared count. Identical or disjoint buffers are supported. A valid empty exchange needs no bus activity. The positive timeout in milliseconds is one finite budget for the whole exchange. `UINT32_MAX` remains finite. A target waiting for external clocks still needs a progressing time source. `Busy` means the exchange could not start. Only the received prefix described by `completed` changes, even on failure.

[ByteExchange](../include/spi/byte_exchange.hpp) extends the same controller in eight-bit mode. It uses packed bytes under the same deadline and prefix rules, and reports `Unsupported` for other configured widths.

## Implementation boundary

The Adapter owns resource state. The caller must keep the implementation and transaction buffers alive during each call and arrange access from other execution contexts. Document the contexts and concurrency guarantees of the actual implementation. Shared public types are in [`spi/types.hpp`](../include/spi/types.hpp).
