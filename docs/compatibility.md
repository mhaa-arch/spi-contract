# Porting the SPI Contract

Hardware Definitions can describe available instances, clock paths and word formats. An Adapter maps the requested width, role, clock mode and rate to combinations it can implement. Recovery and chip-select behavior are target-specific. Reading one's own in-place buffer requires honoring the transmit contents for the transmitted prefix before overwriting it.

This repository's host simulations and shared API compile/link checks provide source-level evidence. Target timing and physical behavior require hardware validation.
