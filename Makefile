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

Disk.img: psboot pskrnl32
	@echo \* Begin image creation...

	cat bootloader/psboot kernel32/pskrnl32 > Disk.img

	@echo \* image creation done!

cleanup:
	make -C kernel32 cleanup

	rm -f bootloader/psboot
	rm -f Disk.img
