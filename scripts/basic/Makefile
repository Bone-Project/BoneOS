###############################################################################
# SPDX-License-Identifier: GPL-3.0-or-later
###############################################################################

.PHONY: all build fixdep clean

all: build
build: fixdep
fixdep: fixdep.o
	@gcc '$<' -o '$@'

%.o: %.c
	@echo '  HOSTCC  scripts/basic/$(@F)'
	@gcc -c '$<' -o '$@'

clean:
	rm -rf *.o
	rm -rf *.cmd
	rm -rf fixdep

###############################################################################