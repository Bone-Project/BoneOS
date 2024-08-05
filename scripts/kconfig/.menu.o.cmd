cmd_scripts/kconfig/menu.o := gcc -Wp,-MMD,scripts/kconfig/.menu.o.d      -c -o scripts/kconfig/menu.o scripts/kconfig/menu.c

source_scripts/kconfig/menu.o := scripts/kconfig/menu.c

deps_scripts/kconfig/menu.o := \
  scripts/kconfig/lkc.h \
    $(wildcard scripts/include/config/prefix) \
  scripts/kconfig/expr.h \
  scripts/kconfig/list.h \
  scripts/kconfig/lkc_proto.h \
  scripts/kconfig/internal.h \

scripts/kconfig/menu.o: $(deps_scripts/kconfig/menu.o)

$(deps_scripts/kconfig/menu.o):
