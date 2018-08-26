##############################################
#
#	Definitions
#
##############################################

NASM32='nasm'

GCC='gcc -std=c++17'
GCC_FLAGS='-c -ffreestanding -Wall -Wpedantic -Iinclude --std=c++17'

LD32='ld'
LD32_FLAGS='i-melf_i386 -T ../elf_i386.x -nostdlib -e _Z11KernelStartv'

OBJCOPY32='objcopy'
OBJCOPY32_FLAGS='-j .text -j .data -j .rodata -j .bss -S -O binary'

BUILD_TEMP='__build'

##############################################
#
#	Make Begin
#
##############################################

all: prepare pskrnl32

prepare:
	mkdir -p $(BUILD_TEMP)

$(BUILD_TEMP)/KernelProtectEntry.bin: KernelProtectEntry.asm
	$(NASM32) -o $@ $<

dep:
	# Dependency
	make -C $(BUILD_TEMP) -f ../makefile InternalDependency

ExecuteInternalBuild: dep
	make -C $(BUILD_TEMP) -f ../makefile KernelEntry32.elf

$(BUILD_TEMP)/KernelEntry32.elf.bin: ExecuteInternalBuild
	$(OBJCOPY)i $(BUILD_TEMP)/KernelEntry32.elf $@

pskrnl32: $(BUILD_TEMP)/KernelProtectEntry.asm $(BUILD_TEMP)/KernelEntry32.elf.bin
	cat $^ > $@

cleanup:
	rm -f *.bin
	rm -f $(BUILD_TEMP)/*
