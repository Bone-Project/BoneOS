cmd_scripts/kconfig/preprocess.o := gcc -Wp,-MMD,scripts/kconfig/.preprocess.o.d      -c -o scripts/kconfig/preprocess.o scripts/kconfig/preprocess.c

source_scripts/kconfig/preprocess.o := scripts/kconfig/preprocess.c

deps_scripts/kconfig/preprocess.o := \
  scripts/kconfig/list.h \
  scripts/kconfig/lkc.h \
    $(wildcard scripts/include/config/prefix) \
  scripts/kconfig/expr.h \
  scripts/kconfig/lkc_proto.h \

scripts/kconfig/preprocess.o: $(deps_scripts/kconfig/preprocess.o)

$(deps_scripts/kconfig/preprocess.o):
