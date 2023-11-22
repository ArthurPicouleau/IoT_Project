APPLICATION = projet

BOARD ?= iotlab-m3

USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ztimer_sec

# lps331ap and isl29020 driver module
USEMODULE +=isl29020
USEMODULE += lps331ap

# Be carreful to set up correctly the path of the RIOT directory
RIOTBASE ?= $(CURDIR)/../../RIOT

include $(RIOTBASE)/Makefile.include
