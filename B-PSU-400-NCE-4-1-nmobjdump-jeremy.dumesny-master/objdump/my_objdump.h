/*
** EPITECH PROJECT, 2021
** B-PSU-400-NCE-4-1-nmobjdump-jeremy.dumesny
** File description:
** my_elf.h
*/

#ifndef OBJDUMP_H_
#define OBJDUMP_H_

#include "../used_fonction/my_elf.h"
#include "../used_fonction/utils.h"
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/mman.h>

#define FAIL -1
#define BFD_NO_FLAGS    0x00
#define HAS_RELOC       0x01
#define EXEC_P          0x02
#define HAS_LINENO      0x04
#define HAS_DEBUG       0x08
#define HAS_SYMS        0x10
#define HAS_LOCALS      0x20
#define DYNAMIC         0x40
#define WP_TEXT         0x80
#define D_PAGED         0x100

int obj_head(const char *filename);
void print_flags_arg(unsigned int flags);
void print_contents(elf_info_t *infos, size_t x);

#endif
