cmd_scripts/kconfig/lxdialog/inputbox.o := gcc -Wp,-MMD,scripts/kconfig/lxdialog/.inputbox.o.d     -D_GNU_SOURCE -c -o scripts/kconfig/lxdialog/inputbox.o scripts/kconfig/lxdialog/inputbox.c

source_scripts/kconfig/lxdialog/inputbox.o := scripts/kconfig/lxdialog/inputbox.c

deps_scripts/kconfig/lxdialog/inputbox.o := \
  scripts/kconfig/lxdialog/dialog.h \

scripts/kconfig/lxdialog/inputbox.o: $(deps_scripts/kconfig/lxdialog/inputbox.o)

$(deps_scripts/kconfig/lxdialog/inputbox.o):
