# Philosopher's Stone
Philosopher's Stone is ~~my own~~ a kernel/OS project.
This project refers the book series named **Principles and Structure of 64bit Multi-core Operating System**, by Seunghoon Han.
 1. http://www.kyobobook.co.kr/product/detailViewKor.laf?barcode=9788979148367
 2. http://www.kyobobook.co.kr/product/detailViewKor.laf?barcode=9788979148374 

## Building Project
To build and get disk image, execute two commands below:

1. `make imagemaker`
2. `make`

Then you will get `Disk.img` that can be loaded on VM or real PC!

## TO-DOs by myself (Maybe more)
These technologies are already exists, but I decided to implement by myself.
 1. KASLR Implementation
 2. Non Executable Stack
 3. Stack Protector
 ---
 4. \<Most Important\> File System for Access Control - PSSFS (PS64 Secure File System) Implementation

 ## Doing Everything By Myself
 Collaborators are joined at the 41th commit, so I cloned this project to try doing everything by myself.

 If you want to see source code of it, Please refer [here](https://github.com/0x00000FF/philosophers-stone-self).
