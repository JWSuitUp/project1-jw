#!/bin/bash
source ../PathSetter.bash
bcc -ansi -c -o kernel.o kernel.c #compile the kernel
as86 kernel.asm -o kernel_asm.o #assemble the kernel.asm file
ld86 -o kernel -d kernel.o kernel_asm.o #link the kernel.o and kernel_asm.o files into the executable kernel file
dd if=kernel of=floppya.img bs=512 conv=notrunc seek=3 #copy the kernel file to sector 3 use
dd if=message.txt of=floppya.img bs=512 conv=notrunc seek=30 #place the provided message.txt file into sector 30 of the disk
dd if=map.img of=floppya.img bs=512 count=1 seek=1 conv=notrunc
dd if=dir.img of=floppya.img bs=512 count=1 seek=2 conv=notrunc
./loadfile message.txt
#load uprog1
as86 lib.asm -o lib.o
bcc -ansi -c -o uprog1.o uprog1.c
ld86 -o uprog1 -d uprog1.o lib.o
./loadfile uprog1

#load uprog2
as86 lib.asm -o lib.o
bcc -ansi -c -o uprog2.o uprog2.c
ld86 -o uprog2 -d uprog2.o lib.o
./loadfile uprog2

#load shell.c
as86 lib.asm -o lib.o
bcc -ansi -c -o shell.o shell.c
ld86 -o shell -d shell.o lib.o
./loadfile shell

#userlib.c
as86 lib.asm -o lib.o
bcc -ansi -c -o userlib.o userlib.c
ld86 -o userlib -d userlib.o lib.o
./loadfile userlib

bochs -f opsys.bxrc
