/*
** EPITECH PROJECT, 2021
** B-PSU-400-NCE-4-1-nmobjdump-jeremy.dumesny
** File description:
** my_elf.h
*/

#ifndef NM_H_
#define NM_H_

#include "../used_fonction/my_elf.h"
#include "../used_fonction/utils.h"

int nm_head(const char *filename, int pos, int max);
char get_symbol(elf_info_t *infos, int i);
char get_other_symbol2(elf_info_t *infos, int i);
char get_other_symbol3(elf_info_t *infos, int i);
char get_other_symbol4(elf_info_t *infos, int i);

#endif
