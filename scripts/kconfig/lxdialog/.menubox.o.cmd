cmd_scripts/kconfig/lxdialog/menubox.o := gcc -Wp,-MMD,scripts/kconfig/lxdialog/.menubox.o.d     -D_GNU_SOURCE -c -o scripts/kconfig/lxdialog/menubox.o scripts/kconfig/lxdialog/menubox.c

source_scripts/kconfig/lxdialog/menubox.o := scripts/kconfig/lxdialog/menubox.c

deps_scripts/kconfig/lxdialog/menubox.o := \
  scripts/kconfig/lxdialog/dialog.h \

scripts/kconfig/lxdialog/menubox.o: $(deps_scripts/kconfig/lxdialog/menubox.o)

$(deps_scripts/kconfig/lxdialog/menubox.o):
