#define O_RDONLY  0x000
#define O_WRONLY  0x001
#define O_RDWR    0x002
#define O_CREATE  0x200

// same with PTE_ in riscv.h, so we can directly
// use the VMA's prot as PTE's permission in trap.c
#define PROT_READ   PTE_R
#define PROT_WRITE  PTE_W

#define MAP_SHARED  0x001
#define MAP_PRIVATE 0x002