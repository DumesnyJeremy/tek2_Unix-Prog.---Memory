/*
** EPITECH PROJECT, 2021
** B-PSU-400-NCE-4-1-nmobjdump-jeremy.dumesny
** File description:
** my_elf.h
*/

#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "sys/stat.h"

void verify_tab(elf_info_t *infos)
{
    int save_sym = infos->sym_shift = -1;
    int save_str = infos->str_shift = -1;
    char *c = infos->strtab;
    for (int x = 0; x < E_SHNUM(infos); x++) {
        int size = SH_NAME(infos, x);
        if (SH_OFFSET(infos, E_SHSTRNDX(infos)) + size 
        >= infos->file_size) {
            printf("File doesn't work\n");
            exit(1);
        }
        if (strcmp(&c[size], ".strtab") == 0)
            save_str = x;
        if (strcmp(&c[size], ".symtab") == 0)
            save_sym = x;
    }
    if (save_sym == -1 || save_str == -1) {
        printf("Error: can't find the symbol");
        exit(1);
    }
    infos->sym_shift = save_sym;
    infos->str_shift = save_str;
}

elf_info_t *create_mmap(elf_info_t *infos, const char *filename, int fd)
{
    infos->file_name = filename;
    lseek(fd, 0, SEEK_SET);
    infos->file_size = lseek(fd, 0, SEEK_END);
    infos->infos = mmap(NULL, infos->file_size, PROT_READ, MAP_SHARED, fd, 0);
    close(fd);
    if (infos->infos == MAP_FAILED)
        return NULL;
    return infos;
}

elf_info_t *initialization_of_mmap(const char *filen, char *p)
{
    elf_info_t *infos;
    int fd = 0;
    char buff[4];
    if ((infos = malloc(sizeof(elf_info_t))) == 0) return NULL;
    struct stat file;
    stat(filen, &file);
    if (S_ISDIR(file.st_mode)) {
        fprintf(stderr, "my_%s: Warning: '%s' is a directory\n", p,filen);
        return NULL;
    }
    if ((fd = open(filen, O_RDONLY)) == -1) {
        fprintf(stderr, "my_%s: '%s': No such file\n", p,filen);
        return NULL;
    }
    lseek(fd, 0, SEEK_SET);
    if (read(fd, buff, 4) != 4 || (buff[0] != 0x7f && buff[1] != 'E' &&
        buff[2] != 'L' && buff[3] != 'F')) {
        fprintf(stderr, "my_%s: %s: file format not recognized\n", p,filen);
        return NULL;
    }
    return (infos = create_mmap(infos, filen, fd));
}

elf_info_t *fill_infos_of_elf(elf_info_t *infos)
{
    if (E_SHOFF(infos) >= infos->file_size) {
        printf("File doesn't work\n");
        exit(1);
    }
    if (infos->types == 0) {
        infos->shdr32 = (Elf32_Shdr *)(infos->infos + E_SHOFF(infos));
    } else
        infos->shdr64 = (Elf64_Shdr *)(infos->infos + E_SHOFF(infos));
    infos->strtab=(char *)(infos->infos + SH_OFFSET(infos, E_SHSTRNDX(infos)));
    verify_tab(infos);
    unsigned int offset = SH_OFFSET(infos, infos->sym_shift);
    if (offset >= infos->file_size) {
        printf("This file doesn't work\n");
        exit(1);
    }
    if (infos->types == 0) {
        infos->sym32 = (infos->infos + offset);
    } else
        infos->sym64 = (infos->infos + offset);
    return infos;
}

elf_info_t *initialization_of_elf(const char *filename, char *prog)
{
    elf_info_t *infos = NULL;
    if ((infos = initialization_of_mmap(filename, prog)) == NULL)
        return NULL;
    void *elf_infos = infos->infos;
    if (((char *)elf_infos)[4] != 2 && ((char *)elf_infos)[4] != 1) {
        printf("Error: wrong type\n");
        exit(1);
    }
    if (((char *)elf_infos)[4] == 1) {
        infos->types = TYPE_32;
        infos->ehdr32 = (Elf32_Ehdr *)elf_infos;
    }
    else {
        infos->types = TYPE_64;
        infos->ehdr64 = (Elf64_Ehdr *)elf_infos;
    }
    return (fill_infos_of_elf(infos));
}
