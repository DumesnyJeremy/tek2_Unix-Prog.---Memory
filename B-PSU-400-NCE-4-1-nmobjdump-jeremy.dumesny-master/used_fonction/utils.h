/*
** EPITECH PROJECT, 2021
** B-PSU-400-NCE-4-1-nmobjdump-jeremy.dumesny
** File description:
** my_elf.h
*/

#ifndef UTILS_H_
#define UTILS_H_

#include "my_elf.h"

elf_info_t *initialization_of_elf(const char *filename, char *prog);
void clean_elf_infos(elf_info_t *infos);

#endif
