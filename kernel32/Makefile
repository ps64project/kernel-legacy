##############################################
#
#	Definitions
#
##############################################

NASM32=nasm

BUILD_TEMP=__build
BUILD_SRC=src

GCC32=gcc
GCC32_FLAGS=--std=c++2a -m32 -c -ffreestanding -O0 -I../$(BUILD_SRC)/include -Wall -Wextra -Wpedantic

LD32=ld
LD32_FLAGS=-melf_i386 -T ../../ldscript/elf_i386.x -nostdlib -e _Z11KernelStartv -Ttext 0x10200

OBJCOPY32=objcopy
OBJCOPY32_FLAGS=-j .text -j .data -j .rodata -j .bss -S -O binary

##############################################
#
#	Make Begin
#
##############################################

all: prepare pskrnl32

prepare:
	mkdir -p $(BUILD_TEMP)

$(BUILD_TEMP)/KernelProtectEntry.bin: $(BUILD_SRC)/KernelProtectEntry.s
	$(NASM32) -o $@ $<

dep:
	# Dependency
	make -C $(BUILD_TEMP) -f ../Makefile InternalDependency

ExecuteInternalBuild: dep
	make -C $(BUILD_TEMP) -f ../Makefile Kernel32.elf

$(BUILD_TEMP)/Kernel32.elf.bin: ExecuteInternalBuild
	$(OBJCOPY32) $(OBJCOPY32_FLAGS) $(BUILD_TEMP)/Kernel32.elf $@

pskrnl32: $(BUILD_TEMP)/KernelProtectEntry.bin $(BUILD_TEMP)/Kernel32.elf.bin
	cat $^ > $@

cleanup:
	rm -f *.bin
	rm -f $(BUILD_TEMP)/*


##############################################
#
#	C++ Kernel Build
#
##############################################

CPPENTRYOBJ=KernelStart.o
CPPSRCFILES=$(wildcard ../$(BUILD_SRC)/*.cpp)
ASMSRCFILES=$(wildcard ../$(BUILD_SRC)/*.asm)
CPPOBJFILES=$(subst KernelEntry32.o, , $(notdir $(patsubst %.cpp, %.o,$(CPPSRCFILES))))
ASMOBJFILES=$(notdir $(patsubst %.asm,%.o,$(ASMSRCFILES)))

%.o: ../$(BUILD_SRC)/%.cpp
	$(GCC32) $(GCC32_FLAGS) $<

%.o: ../$(BUILD_SRC)/%.asm
	$(NASM32) -f elf32 -o $@ $<

InternalDependency:
	$(GCC32) $(GCC32_FLAGS) -MM $(CPPSRCFILES) > Dependency.dep

Kernel32.elf: $(CPPENTRYOBJ) $(CPPOBJFILES) $(ASMOBJFILES)
	$(LD32) $(LD32_FLAGS) -o $@ $^

ifeq (Dependency.dep, $(wildcard Dependency.dep))
include Dependency.dep
endif
