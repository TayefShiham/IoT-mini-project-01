BOARD ?= nrf52dk
include ../Makefile.pkg_common

# include shell support
USEMODULE += shell_cmds_default
USEMODULE += ps

# Include GNRC and RPL
USEMODULE += auto_init_gnrc_netif
USEMODULE += gnrc_ipv6_router_default
USEMODULE += auto_init_gnrc_rpl
USEMODULE += gnrc_rpl
USEMODULE += gnrc_icmpv6_echo

# Setup Nimble
USEMODULE += nimble_netif
USEMODULE += nimble_statconn

TEST_ON_CI_WHITELIST += nrf52dk

include $(RIOTBASE)/Makefile.include
