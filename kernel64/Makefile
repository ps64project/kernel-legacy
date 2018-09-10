##############################################
#
#	Definitions
#
##############################################

NASM=nasm -f elf64

BUILD_TEMP=__build
BUILD_SRC=src

GCC64=gcc
GCC64_FLAGS=--std=c++2a -m64 -c -ffreestanding -fdata-sections -ffunction-sections -fno-stack-protector -fno-threadsafe-statics -nostdlib -O0 -I../$(BUILD_SRC)/include -Wall -Wextra -Wpedantic -Wl,--gc-sections

LD64=ld
LD64_FLAGS=-melf_x86_64 -T ../../ldscript/x86_64.x -nostdlib -e _Z11KernelStartv -Ttext 0x200000

OBJCOPY64=objcopy
OBJCOPY64_FLAGS=-j .text -j .data -j .rodata -j .bss -S -O binary

##############################################
#
#	Make Begin
#
##############################################

all: prepare pskrnl64

prepare:
	mkdir -p $(BUILD_TEMP)

dep:
	# Dependency
	make -C $(BUILD_TEMP) -f ../Makefile InternalDependency

ExecuteInternalBuild: dep
	make -C $(BUILD_TEMP) -f ../Makefile Kernel64.elf

$(BUILD_TEMP)/Kernel64.elf.bin: ExecuteInternalBuild
	$(OBJCOPY32) $(OBJCOPY32_FLAGS) $(BUILD_TEMP)/Kernel64.elf $@

pskrnl64: $(BUILD_TEMP)/Kernel64.elf.bin
	mv $@ $<

cleanup:
	rm -f pskrnl64
	rm -f $(BUILD_TEMP)/*


##############################################
#
#	C++ IA-32e Kernel Build
#
##############################################

ENTRYSRC=../$(SOURCEDIRECTORY)/KernelEntry.s
ENTRYOBJ=KernelEntry64.o

CPPENTRYOBJ=KernelStart.o
CPPSRCFILES=$(wildcard ../$(BUILD_SRC)/*.cpp)
ASMSRCFILES=$(wildcard ../$(BUILD_SRC)/*.asm)
CPPOBJFILES=$(subst KernelEntry64.o, , $(notdir $(patsubst %.cpp, %.o,$(CPPSRCFILES))))
ASMOBJFILES=$(notdir $(patsubst %.asm,%.o,$(ASMSRCFILES)))

$(ENTRYOBJ): $(ENTRYSRC)
	$(NASM) -o $@ $<

%.o: ../$(BUILD_SRC)/%.cpp
	$(GCC64) $(GCC64_FLAGS) $<

%.o: ../$(BUILD_SRC)/%.asm
	$(NASM) -o $@ $<

InternalDependency:
	$(GCC64) $(GCC64_FLAGS) -MM $(CPPSRCFILES) > Dependency.dep

Kernel64.elf: $(CPPENTRYOBJ) $(CPPOBJFILES) $(ASMOBJFILES)
	$(LD64) $(LD64_FLAGS) -o $@ $^

ifeq (Dependency.dep, $(wildcard Dependency.dep))
include Dependency.dep
endif
