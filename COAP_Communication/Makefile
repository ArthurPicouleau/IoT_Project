APPLICATION = coap_communication

BOARD ?= iotlab-m3

# Be carreful to set up correctly the path of the RIOT directory
RIOTBASE ?= $(CURDIR)/../../RIOT


GCOAP_RESEND_BUFS_MAX ?= 2
CFLAGS += -DCONFIG_GCOAP_RESEND_BUFS_MAX=$(GCOAP_RESEND_BUFS_MAX)

USEMODULE += netdev_default
USEMODULE += auto_init_gnrc_netif
USEMODULE += gnrc_ipv6_default
USEMODULE += gcoap
USEMODULE += gnrc_icmpv6_echo

USEMODULE += od
USEMODULE += fmt
# Shell and some shell commands
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps

# lps331ap and isl29020 driver module
USEMODULE += lps331ap
USEMODULE +=isl29020

DEVELHELP ?= 1


QUIET ?= 1

include $(RIOTBASE)/Makefile.include

include $(RIOTMAKE)/default-radio-settings.inc.mk
