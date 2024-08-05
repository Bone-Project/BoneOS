###############################################################################
# SPDX-License-Identifier: GPL-3.0-or-later
###############################################################################

.PHONY: fixdep %config clean force

VERSION = 6
PATCHLEVEL = 2
SUBLEVEL = 0
EXTRAVERSION =
NAME = Hurr durr I'ma ninja sloth

KBUILD_VERBOSE = 0
quiet = quiet_
Q = @

srctree = $(CURDIR)
objtree = $(CURDIR)

export KBUILD_VERBOSE quiet Q srctree objtree

include scripts/Kbuild.include

KCONFIG_CONFIG = .config
KCONFIG_AUTOHEADER = kconfig.h
KCONFIG_AUTOCONFIG = scripts/include/config/auto.conf
KCONFIG_TRISTATE = scripts/include/config/tristate.conf
KCONFIG_RUSTCCFG = scripts/include/generated/rustc_cfg

export KCONFIG_CONFIG KCONFIG_AUTOHEADER KCONFIG_AUTOCONFIG \
       KCONFIG_TRISTATE KCONFIG_RUSTCCFG

# SHELL used by kbuild
CONFIG_SHELL := $(shell if [ -x "$$BASH" ]; then echo $$BASH; \
                else if [ -x /bin/bash ]; then echo /bin/bash; \
                else echo sh; fi ; fi)

HOSTCC       = gcc
HOSTCXX      = g++
HOSTCFLAGS   = -O2 -Wall -Wextra
HOSTCXXFLAGS = -O2 -Wall -Wextra

export CONFIG_SHELL HOSTCC HOSTCXX HOSTCFLAGS HOSTCXXFLAGS

%config: fixdep force
	@$(MAKE) $(build)=scripts/kconfig $@
	@$(MAKE) $(build)=scripts/kconfig syncconfig

fixdep:
	@cd scripts/basic && make

clean:
	@cd scripts/basic && make --no-print-directory clean
	rm -rf scripts/include
	rm -rf scripts/kconfig/*.o
	rm -rf scripts/kconfig/lxdialog/*.o
	rm -rf scripts/kconfig/lxdialog/.*.cmd
	rm -rf scripts/kconfig/.*.cmd
	rm -rf scripts/kconfig/*.tmp
	rm -rf scripts/kconfig/conf
	rm -rf scripts/kconfig/lexer.lex.c
	rm -rf scripts/kconfig/mconf
	rm -rf scripts/kconfig/mconf-bin
	rm -rf scripts/kconfig/mconf-cfg
	rm -rf scripts/kconfig/mconf-cflags
	rm -rf scripts/kconfig/mconf-libs
	rm -rf scripts/kconfig/parser.tab.*

force:

###############################################################################