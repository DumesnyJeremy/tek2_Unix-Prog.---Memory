/*
** EPITECH PROJECT, 2021
** B-PSU-400-NCE-4-1-nmobjdump-jeremy.dumesny
** File description:
** my_elf.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/mman.h>
#include "my_objdump.h"

int print_flags(elf_info_t *infos)
{
    int flag = 0x0000;

    if (E_TYPE(infos) == ET_EXEC)
        flag += EXEC_P + D_PAGED;
    else if (E_TYPE(infos) == ET_DYN)
        flag += DYNAMIC + D_PAGED;
    if (E_TYPE(infos) == ET_REL && E_TYPE(infos) != ET_EXEC &&
        E_TYPE(infos) != ET_DYN)
        flag += HAS_RELOC;
    for (size_t i = 0; i < E_SHNUM(infos); i++)
        if (SH_TYPE(infos, i) == SHT_SYMTAB)
            return (flag + HAS_SYMS);
    return flag;
}

void print_header(elf_info_t *infos)
{
    printf("\n%s:\tfile format %s\n", infos->file_name,
            (T_64(infos) ? "elf64-x86-64" : "elf32-i386"));
    if (E_MACHINE(infos) == EM_X86_64 || E_MACHINE(infos) == EM_386)
    printf("architecture: %s", (E_MACHINE(infos) == EM_X86_64 ?
        "i386:x86-64" : "i386"));
    else
        printf("architecture: %d", (E_MACHINE(infos)));
    unsigned int result_flags = print_flags(infos);
    printf(", flags 0x%08x:\n", result_flags);
    print_flags_arg(result_flags);
    if (infos->types == 0)
        printf("start address 0x%08x\n\n", infos->ehdr32->e_entry);
    else
        printf("start address 0x%016lx\n\n", infos->ehdr64->e_entry);
}

int obj_head(const char *filename)
{
    elf_info_t *infos = NULL;
    if ((infos = initialization_of_elf(filename, "objdump")) == NULL) {
        return -1;
    }
    print_header(infos);
    for (size_t x = 0; x < E_SHNUM(infos); x++) {
        print_contents(infos, x);
    }
    munmap(infos->infos, infos->file_size);
    free(infos);
    return (0);
}