/*
** EPITECH PROJECT, 2021
** B-PSU-400-NCE-4-1-nmobjdump-jeremy.dumesny
** File description:
** my_elf.h
*/

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <sys/mman.h>
#include "my_nm.h"

void print_bits(elf_info_t *infos, char symbole, char *string_to_print, int x)
{
    if (BIND_ST_INFO(infos, x) == STB_LOCAL && symbole != '?')
        symbole += 32;
    if (infos->types == 1) {
        if (symbole != 'A' && symbole != 'a') {
            if (ST_SHNDX(infos, x) == SHN_UNDEF)
                printf("                 ");
            else
                printf("%016x ", (unsigned int)ST_VALUE(infos, x));
            printf("%c %s\n", symbole, string_to_print);
        }
    } else {
        if (symbole != 'A' && symbole != 'a') {
            if (ST_SHNDX(infos, x) == SHN_UNDEF)
                printf("         ");
            else
                printf("%08x ", (unsigned int)ST_VALUE(infos, x));
            printf("%c %s\n", symbole, string_to_print);
        }
    }
}

char get_other_symbol(elf_info_t *inf, int x)
{
    if (TYPE_ST_INFO(inf,x)==STT_FUNC&&SH_FLAGS(inf,ST_SHNDX(inf,x))==0 &&
        SH_TYPE(inf, ST_SHNDX(inf, x)) == SHT_NULL)
        return 'U';
    if (TYPE_ST_INFO(inf, x) == STT_OBJECT && SH_FLAGS(inf, ST_SHNDX(inf, x))
        == 50 && SH_TYPE(inf, ST_SHNDX(inf, x)) == SHT_PROGBITS)
        return 'R';
    if (TYPE_ST_INFO(inf, x) == STT_NOTYPE && SH_FLAGS(inf,ST_SHNDX(inf,
        x)) == 50 && SH_TYPE(inf, ST_SHNDX(inf, x)) == SHT_PROGBITS)
        return 'R';
    if (TYPE_ST_INFO(inf, x) == STT_NOTYPE && SH_FLAGS(inf,ST_SHNDX(inf, x))
        == 2 && SH_TYPE(inf, ST_SHNDX(inf, x)) == SHT_PROGBITS)
        return 'R';
    if (TYPE_ST_INFO(inf, x) == STT_OBJECT && SH_FLAGS(inf, ST_SHNDX(inf, x))
        == 2 && SH_TYPE(inf, ST_SHNDX(inf, x)) == SHT_PROGBITS)
        return 'R';
    if (TYPE_ST_INFO(inf, x) == STT_OBJECT && SH_FLAGS(inf,
        ST_SHNDX(inf, x)) == 2 && SH_TYPE(inf, ST_SHNDX(inf, x)) == SHT_NOTE)
        return 'R';
    return (get_other_symbol2(inf, x));
}

char get_symbol_char(elf_info_t *infos, int i)
{
    char symbol = get_symbol(infos, i);
    if (symbol == '0')
    {
        return (symbol = get_other_symbol(infos, i));
    }
    else
    {
        return symbol;
    }
}

void parse_infos(elf_info_t *infos)
{
    int x = 0, types = 0, sos =(int)(SH_SIZE(infos, infos->sym_shift));
    char *string_to_print = NULL;
    if (infos->types == 0)
        types = sizeof(Elf32_Sym);
    else
        types = sizeof(Elf64_Sym);
    for (; x < sos / types; x++) {
        int size = SH_OFFSET(infos, infos->str_shift);
        if (size + ST_NAME(infos, x) >=
            infos->file_size) {
            printf("Error: Can't work with this file\n");
            exit(1);
        }
        string_to_print = (char *)(infos->infos + size + ST_NAME(infos, x));
        if (strcmp("", string_to_print) != 0 && string_to_print) {
            char symbol = get_symbol_char(infos, x);
            print_bits(infos, symbol, string_to_print, x);
        }
    }
}

int nm_head(const char *filename, int pos, int max)
{
    elf_info_t *infos = NULL;
    if ((infos = initialization_of_elf(filename, "nm")) == NULL ) {
        return -1;
    }
    if (pos + 1 && max > 2)
        printf("\n");
    if (pos != 1 || max != 2)
        printf("%s:\n", filename);
    parse_infos(infos);
    munmap(infos->infos, infos->file_size);
    free(infos);
    return (0);
}