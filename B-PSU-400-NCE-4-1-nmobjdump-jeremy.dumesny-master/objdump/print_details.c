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

static char* contents[11] = {".bss", ".symtab", ".shstrtab", ".strtab",
".rela.debug_line", ".rela.debug_aranges", ".rela.debug_info", ".tbss",
".rela.text", ".rela.eh_frame", "__libc_freeres_ptrs"};

static void print_details(size_t x, size_t size, uint8_t *nbr)
{
    if (x < size) {
        if (nbr[x] <= '~' && nbr[x] >= ' ')
            printf("%c", nbr[x]);
        else
            printf(".");
    } else {
        printf(" ");
    }
}

static void print_hexa_value(void *value, size_t size)
{
    uint8_t *hexa = value;
    size_t index = 0;

    for (; index < 16; index++) {
        if (index < size)
            printf("%02x", hexa[index]);
        else
            printf("  ");
        if (!((index + 1) % 4))
            printf(" ");
    }
    printf(" ");
    for (index = 0; index < 16; index ++)
        print_details(index, size, hexa);
}

static void display_content(elf_info_t *infos, size_t x)
{
    size_t offset = SH_OFFSET(infos, x);

    for (; offset < (size_t)(SH_SIZE(infos, x) + SH_OFFSET(infos, x));
    offset += 16) {
        printf(" %04x ",(int)(SH_ADDR(infos, x) + offset-SH_OFFSET(infos, x)));
        if (infos->types == 0) {
            print_hexa_value((void *)infos->ehdr32 + offset, 
            SH_OFFSET(infos, x) + SH_SIZE(infos, x) - offset);
        } else if (infos->types == 1) {
            print_hexa_value((void *)infos->ehdr64 + offset,
            SH_OFFSET(infos, x) + SH_SIZE(infos, x) - offset);
        }
        printf("\n");
    }
}

bool section_is_correct(elf_info_t *infos, size_t x)
{
    if (SH_SIZE(infos, x) <= 0)
        return false;
    for (size_t size = 0; size < 11; size++) {
        if (infos->types == 0) {
            if (!strcmp(contents[size], &CONTENT_32[SH_NAME(infos, x)]))
                return false;
        } else if (infos->types == 1) {
            if (!strcmp(contents[size], &CONTENT_64[SH_NAME(infos, x)]))
                return false;
        }

    }
    return true;
}

void print_contents(elf_info_t *infos, size_t x)
{
    if (section_is_correct(infos, x)) {
        if (infos->types == 0)
            printf("Contents of section %s:\n", 
            &CONTENT_32[SH_NAME(infos, x)]);
        else if (infos->types == 1)
            printf("Contents of section %s:\n",
            &CONTENT_64[SH_NAME(infos, x)]);
        display_content(infos, x);
    }
}