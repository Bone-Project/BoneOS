#!/bin/bash
grep '^#define' "$1" | sed 's/#define \([^ ]*\) *\(.*\)/\1=\2/' | sed 's/\"//g' > kconfig.mk