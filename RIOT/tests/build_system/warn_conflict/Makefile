BOARD ?= stm32f4discovery
include ../Makefile.build_system_common

# The stm32f4discovery is the only board that provides known conflicting features,
# so using this compile test on other boards will not provide the expected warning.
BOARD_WHITELIST := stm32f4discovery

# These features have a chance to use/access the shared `SPI_DEV(0)` on
# stm32f4discovery, which would probably produce an unexpected behavior in the
# user application.
FEATURES_REQUIRED = periph_dac periph_spi

include $(RIOTBASE)/Makefile.include
