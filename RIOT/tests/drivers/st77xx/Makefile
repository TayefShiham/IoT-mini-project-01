BOARD ?= stm32f429i-disc1

include ../Makefile.drivers_common

ST7789_BOARDS = \
  esp32s2-lilygo-ttgo-t8 \
  esp32s3-usb-otg \
  stm32f723e-disco \
  stm32l496g-disco \
  #

ST7796_BOARDS = \
  esp32s3-wt32-sc01-plus \
  #

ifneq (,$(filter $(ST7789_BOARDS),$(BOARD)))
  DRIVER ?= st7789
endif
ifneq (,$(filter $(ST7796_BOARDS),$(BOARD)))
  DRIVER ?= st7796
endif

DRIVER ?= st7735

USEMODULE += $(DRIVER)
USEMODULE += ztimer
USEMODULE += ztimer_msec

# As there is an 'Kconfig' we want to explicitly disable Kconfig by setting
# the variable to empty
SHOULD_RUN_KCONFIG ?=

# add include path for riot_logo.h
INCLUDES += -I$(RIOTBASE)/tests

include $(RIOTBASE)/Makefile.include

# Check if being configured via Kconfig
ifndef CONFIG_KCONFIG_USEMODULE_LCD
  CFLAGS += -DCONFIG_LCD_LE_MODE

  # The AVR architecture stores the image in the RAM, this usually doesn't fit.
  # This flag excludes the image from the test
  ifneq (,$(filter arch_avr8,$(FEATURES_USED)))
    CFLAGS += -DCONFIG_NO_RIOT_IMAGE
  endif
endif
