
# Common phony targets
.PHONY: all clean

#
# C, C++, Assembly autodependencies and compilation
#

# Directory to store auto-generated dependency makefile fragments
DEPDIR := .d

# Make sure dependency file directory exists
$(shell mkdir -p $(DEPDIR) >/dev/null)

# Flags to use when generating autodependencies
DEPFLAGS = -MMD -MP -MF $(DEPDIR)/$(notdir $*).Td
#-MT $@

DEPFLAGS.nasm = -MD $(DEPDIR)/$(notdir $*).Td

OUTPUT_OPTION = -o $@

# Compile commands for C and C++
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) $(OUTPUT_OPTION) -c
COMPILE.cc = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) $(OUTPUT_OPTION) -c
COMPILE.s = $(AS) $(ASFLAGS) $(TARGET_ARCH_AS) $(OUTPUT_OPTION) -c
COMPILE.asm = $(NASM) $(NASMFLAGS) $(TARGET_ARCH_NASM)
COMPILE.as = $(AS) $(DEPFLAGS) $(ASFLAGS) $(OUTPUT_OPTION) -c

# Command to move generated dependency files into separate directory
POSTCOMPILE = mv -f $(DEPDIR)/$(notdir $*).Td $(DEPDIR)/$(notdir $*).d

.s.o:
	$(COMPILE.as) $<

.asm.o:
	$(COMPILE.asm) $(OUTPUT_OPTION) $(DEPFLAGS.nasm) $<
	$(POSTCOMPILE)

.c.o:
	$(COMPILE.c) $<
	$(POSTCOMPILE)

.SUFFIXES: .asm

ifdef DISASSEMBLEFLAGS
# Disassemble
$(DUMPDIR)/%.dis : $(BINDIR)/%.bin
$(DUMPDIR)/%.dis : $(BINDIR)/%.bin
	objdump $(DISASSEMBLEFLAGS) $< > $@
endif

# Hex Dump
$(DUMPDIR)/%.hex : $(BINDIR)/%.bin
$(DUMPDIR)/%.hex : $(BINDIR)/%.bin
	hexdump -C $< > $@

# Tolerate the dependency files being missing
$(DEPDIR)/%.d: ;

# Prevent deletion of generated dependencies
.PRECIOUS: $(DEPDIR)/%.d

# Include the generated makefile fragments
-include $(patsubst %,$(DEPDIR)/%.d,$(notdir $(basename $(CSRCS))))
