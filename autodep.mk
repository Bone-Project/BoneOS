
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
COMPILE.asm = $(NASM) $(OUTPUT_OPTION) $(NASMFLAGS) $(TARGET_ARCH_NASM)

# Command to move generated dependency files into separate directory
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d


.asm.o:
	$(COMPILE.asm) $(OUTPUT_OPTION) $(DEPFLAGS.nasm) $<

.c.o:
	$(COMPILE.c) $<

.SUFFIXES: .asm

## Compile assembly
#%.o : %.s
#	$(COMPILE.s) $(OUTPUT_OPTION) $<
#
## Compile C
#.o : .c
#.o : .c $(dirname %)/$(DEPDIR)/$(basename %).d
#	$(COMPILE.c) $(OUTPUT_OPTION) $<
#	$(POSTCOMPILE)
#
## Generate assembly dump for C
#$(DUMPDIR)/%.s : %.c
#$(DUMPDIR)/%.s : %.c $(DEPDIR)/%.d
#	$(COMPILE.c) $(OUTPUT_OPTION) -S $<
#	$(POSTCOMPILE)
#
## Compile C++ with cc extension
#%.o : %.cc
#%.o : %.cc $(DEPDIR)/%.d
#	$(COMPILE.cc) $(OUTPUT_OPTION) $<
#	$(POSTCOMPILE)
#
## Compile C++ with cxx extension
#%.o : %.cxx
#%.o : %.cxx $(DEPDIR)/%.d
#	$(COMPILE.cc) $(OUTPUT_OPTION) $<
#	$(POSTCOMPILE)
#
## Compile C++ with cpp extension
#%.o : %.cpp
#%.o : %.cpp $(DEPDIR)/%.d
#	$(COMPILE.cc) $(OUTPUT_OPTION) $<
#	$(POSTCOMPILE)
#
#ifdef DISASSEMBLEFLAGS
## Disassemble
#$(DUMPDIR)/%.dis : $(BINDIR)/%.bin
#$(DUMPDIR)/%.dis : $(BINDIR)/%.bin
#	objdump $(DISASSEMBLEFLAGS) $< > $@
#endif
#
## Hex Dump
#$(DUMPDIR)/%.hex : $(BINDIR)/%.bin
#$(DUMPDIR)/%.hex : $(BINDIR)/%.bin
#	hexdump -C $< > $@

# Tolerate the dependency files being missing
$(DEPDIR)/%.d: ;

# Prevent deletion of generated dependencies
.PRECIOUS: $(DEPDIR)/%.d

# Include the generated makefile fragments
-include $(patsubst %,$(DEPDIR)/%.d,$(notdir $(basename $(CSRCS))))
