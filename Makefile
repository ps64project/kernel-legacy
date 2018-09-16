# PS64 Build Makefile

all: psboot pskrnl32 Disk.img

psboot:
	@echo \* Begin psboot bootloader assemble...

	nasm bootloader/psboot.asm

	@echo \* Bootloader preparation complete...

pskrnl32:
	@echo \* Begin PS64 protected mode kernel build....

	make -C kernel32

	@echo \* pm kernel preparation complete...

pskrnl64:
	@echo \* Begin PS64 IA-32e mode kernel build....

	make -C kernel64

	@echo \* IA-32e kernel preparation complete...

Disk.img: psboot pskrnl32 pskrnl64 imgcreator
	@echo \* Begin image creation...

	./imagecreator bootloader/psboot kernel32/pskrnl32 kernel64/pskrnl64

	@echo \* image creation done!

imagecreator:
	g++ --std=c++2a -o imagecreator imgcreator/ImageCreator.cpp

cleanup:
	make -C kernel32 cleanup
	make -C kernel64 cleanup

	rm -f bootloader/psboot
	rm -f Disk.img
