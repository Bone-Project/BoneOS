cmd_scripts/kconfig/confdata.o := gcc -Wp,-MMD,scripts/kconfig/.confdata.o.d      -c -o scripts/kconfig/confdata.o scripts/kconfig/confdata.c

source_scripts/kconfig/confdata.o := scripts/kconfig/confdata.c

deps_scripts/kconfig/confdata.o := \
    $(wildcard scripts/include/config/FOO) \
    $(wildcard scripts/include/config/X) \
  scripts/kconfig/lkc.h \
    $(wildcard scripts/include/config/prefix) \
  scripts/kconfig/expr.h \
  scripts/kconfig/list.h \
  scripts/kconfig/lkc_proto.h \

scripts/kconfig/confdata.o: $(deps_scripts/kconfig/confdata.o)

$(deps_scripts/kconfig/confdata.o):
