#!/bin/bash
bcc -ansi -c -o kernel.o kernel.c #compile the kernel
as86 kernel.asm -o kernel_asm.o #assemble the kernel.asm file
ld86 -o kernel -d kernel.o kernel_asm.o #link the kernel.o and kernel_asm.o files into the executable kernel file
dd if=kernel of=floppya.img bs=512 conv=notrunc seek=3 #copy the kernel file to sector 3 use