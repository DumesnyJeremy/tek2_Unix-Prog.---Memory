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

void print_flags_arg4(unsigned int flags, int is_end)
{
    if ((BFD_NO_FLAGS & flags) && is_end)
        printf(", %s", "BFD_NO_FLAGS");
    else if (BFD_NO_FLAGS & flags) {
        printf("%s", "BFD_NO_FLAGS");
        is_end = 1;
    }
    printf("\n");
}

void print_flags_arg3(unsigned int flags, int is_end)
{
    if ((DYNAMIC & flags) && is_end)
        printf(", %s", "DYNAMIC");
    else if (DYNAMIC & flags) {
        printf("%s", "DYNAMIC");
        is_end = 1;
    }
    if ((WP_TEXT & flags) && is_end)
        printf(", %s", "WP_TEXT");
    else if (WP_TEXT & flags) {
        printf("%s", "WP_TEXT");
        is_end = 1;
    }
    if ((D_PAGED & flags) && is_end)
        printf(", %s", "D_PAGED");
    else if (D_PAGED & flags) {
        printf("%s", "D_PAGED");
        is_end = 1;
    }
    print_flags_arg4(flags, is_end);
}

void print_flags_arg2(unsigned int flags, int is_end)
{
    if ((HAS_DEBUG & flags) && is_end)
        printf(", %s", "HAS_DEBUG");
    else if (HAS_DEBUG & flags) {
        printf("%s", "HAS_DEBUG");
        is_end = 1;
    }
    if ((HAS_SYMS & flags) && is_end)
        printf(", %s", "HAS_SYMS");
    else if (HAS_SYMS & flags) {
        printf("%s", "HAS_SYMS");
        is_end = 1;
    }
    if ((HAS_LOCALS & flags) && is_end)
        printf(", %s", "HAS_LOCALS");
    else if (HAS_LOCALS & flags) {
        printf("%s", "HAS_LOCALS");
        is_end = 1;
    }
    print_flags_arg3(flags, is_end);
}

void print_flags_arg(unsigned int flags)
{
    int is_end = 0;
    if ((HAS_RELOC & flags) && is_end)
        printf(", %s", "HAS_RELOC");
    else if (HAS_RELOC & flags) {
        printf("%s", "HAS_RELOC");
        is_end = 1;
    }
    if ((EXEC_P & flags) && is_end)
        printf(", %s", "EXEC_P");
    else if (EXEC_P & flags) {
        printf("%s", "EXEC_P");
        is_end = 1;
    }
    if ((HAS_LINENO & flags) && is_end)
        printf(", %s", "HAS_LINENO");
    else if (HAS_LINENO & flags) {
        printf("%s", "HAS_LINENO");
        is_end = 1;
    }
    print_flags_arg2(flags, is_end);
}