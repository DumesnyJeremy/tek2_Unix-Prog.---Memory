/*
** EPITECH PROJECT, 2021
** B-PSU-400-NCE-4-1-nmobjdump-jeremy.dumesny
** File description:
** my_elf.h
*/

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "my_nm.h"

char get_weak_symbols(elf_info_t *infos, int x)
{
    if ((TYPE_ST_INFO(infos, x) == STT_OBJECT) &&
        ST_SHNDX(infos, x) == SHN_UNDEF)
        return 'v';
    if (TYPE_ST_INFO(infos, x) == STT_OBJECT)
        return 'V';
    if (ST_SHNDX(infos, x) == SHN_UNDEF)
        return 'w';
    return 'W';
}

char get_symbol(elf_info_t *infos, int x)
{
    if (BIND_ST_INFO(infos, x) == STB_WEAK)
    {
        return (get_weak_symbols(infos, x));
    }
    if (BIND_ST_INFO(infos, x) == STB_GNU_UNIQUE)
    {
        return 'u';
    }
    if (ST_SHNDX(infos, x) == SHN_COMMON)
        return ('C');
    if (ST_SHNDX(infos, x) == SHN_UNDEF) {
        return ('U');
    }
    if (ST_SHNDX(infos, x) == SHN_ABS)
        return ('A');
    else
    {
        return '0';
    }
}

char get_other_symbol4(elf_info_t *infos, int x)
{
    if (TYPE_ST_INFO(infos, x) == STT_OBJECT && SH_FLAGS(infos, ST_SHNDX
        (infos, x)) == 0 && SH_TYPE(infos, ST_SHNDX(infos, x)) == SHT_PROGBITS)
        return 'N';
    if (TYPE_ST_INFO(infos, x) == STT_TLS && SH_FLAGS(infos, ST_SHNDX(infos,
        x)) == 1027 && SH_TYPE(infos, ST_SHNDX(infos, x)) == SHT_NOBITS)
        return 'B';
    if (TYPE_ST_INFO(infos, x) == STT_OBJECT && SH_FLAGS(infos, ST_SHNDX(infos,
        x)) == 3 && SH_TYPE(infos, ST_SHNDX(infos, x)) == SHT_NOBITS)
        return 'B';
    if (TYPE_ST_INFO(infos, x) == STT_NOTYPE && SH_FLAGS(infos, ST_SHNDX(infos,
        x)) == 3 && SH_TYPE(infos, ST_SHNDX(infos, x)) == SHT_NOBITS)
        return 'B';
    if (TYPE_ST_INFO(infos, x) == STT_LOOS && SH_FLAGS(infos, ST_SHNDX(infos,
        x)) == 6 && SH_TYPE(infos, ST_SHNDX(infos, x)) == SHT_PROGBITS)
        return 'I';
    return '?';
}

char get_other_symbol3(elf_info_t *infos, int x)
{
    if (TYPE_ST_INFO(infos, x) == STT_OBJECT && SH_FLAGS(infos, ST_SHNDX(infos,
        x)) == 3 && SH_TYPE(infos, ST_SHNDX(infos, x)) == SHT_FINI_ARRAY)
        return 'T';
    if (TYPE_ST_INFO(infos, x) == STT_OBJECT && SH_FLAGS(infos, ST_SHNDX(infos,
        x)) == 3 && SH_TYPE(infos, ST_SHNDX(infos, x)) == SHT_DYNAMIC)
        return 'D';
    if (TYPE_ST_INFO(infos, x) == STT_TLS && SH_FLAGS(infos, ST_SHNDX(infos,
        x)) == 1027 && SH_TYPE(infos, ST_SHNDX(infos, x)) == SHT_PROGBITS)
        return 'D';
    if (TYPE_ST_INFO(infos, x) == STT_NOTYPE && SH_FLAGS(infos, ST_SHNDX(infos,
        x)) == 3 && SH_TYPE(infos, ST_SHNDX(infos, x)) == SHT_PROGBITS)
        return 'D';
    if (TYPE_ST_INFO(infos, x) == STT_OBJECT && SH_FLAGS(infos, ST_SHNDX(infos,
        x)) == 3 && SH_TYPE(infos, ST_SHNDX(infos, x)) == SHT_PROGBITS)
        return 'D';
    if (TYPE_ST_INFO(infos, x) == STT_NOTYPE && SH_FLAGS(infos, ST_SHNDX(infos,
        x)) == 0 && SH_TYPE(infos, ST_SHNDX(infos, x)) == SHT_PROGBITS)
        return 'N';
    return get_other_symbol4(infos, x);
}

char get_other_symbol2(elf_info_t *infos, int x)
{
    if (TYPE_ST_INFO(infos, x) == SHF_WRITE && SH_FLAGS(infos, ST_SHNDX(infos,
        x)) == 18 && SH_TYPE(infos, ST_SHNDX(infos, x)) == SHT_PROGBITS)
        return 'R';
    if (TYPE_ST_INFO(infos, x) == STT_OBJECT && SH_FLAGS(infos, ST_SHNDX(infos,
        x)) == 3 && SH_TYPE(infos, ST_SHNDX(infos, x)) == SHT_INIT_ARRAY)
        return 'T';
    if (TYPE_ST_INFO(infos, x) == STT_NOTYPE && SH_FLAGS(infos, ST_SHNDX(infos,
        x)) == 3 && SH_TYPE(infos, ST_SHNDX(infos, x)) == SHT_INIT_ARRAY)
        return 'T';
    if (TYPE_ST_INFO(infos, x) == STT_FUNC && SH_FLAGS(infos, ST_SHNDX(infos,
        x)) == 6 && SH_TYPE(infos, ST_SHNDX(infos, x)) == SHT_PROGBITS)
        return 'T';
    if (TYPE_ST_INFO(infos, x) == STT_NOTYPE && SH_FLAGS(infos, ST_SHNDX(infos,
        x)) == 6 && SH_TYPE(infos, ST_SHNDX(infos, x)) == SHT_PROGBITS)
        return 'T';
    if (TYPE_ST_INFO(infos, x) == STT_NOTYPE && SH_FLAGS(infos, ST_SHNDX(infos,
        x)) == 3 && SH_TYPE(infos, ST_SHNDX(infos, x)) == SHT_FINI_ARRAY)
        return 'T';
    return get_other_symbol3(infos, x);
}