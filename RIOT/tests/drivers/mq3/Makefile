include ../Makefile.drivers_common

USEMODULE += mq3
USEMODULE += xtimer

# set default device parameters in case they are undefined
MQ3_ADC_LINE  ?= ADC_LINE\(0\)

# export parameters
CFLAGS += -DMQ3_ADC_LINE=$(MQ3_ADC_LINE)

include $(RIOTBASE)/Makefile.include
