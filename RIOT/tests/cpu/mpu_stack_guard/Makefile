BOARD ?= nucleo-f767zi

include ../Makefile.cpu_common

USEMODULE += mpu_stack_guard

include $(RIOTBASE)/Makefile.include

ifeq (llvm,$(TOOLCHAIN))
  CFLAGS += -Wno-infinite-recursion
endif
