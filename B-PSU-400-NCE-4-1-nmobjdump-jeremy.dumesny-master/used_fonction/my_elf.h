/*
** EPITECH PROJECT, 2021
** B-PSU-400-NCE-4-1-nmobjdump-jeremy.dumesny
** File description:
** my_elf.h
*/

#ifndef MY_ELF_H_
#define MY_ELF_H_

#include <elf.h>
#include <stdbool.h>

#define T_32(inf) (inf->types == TYPE_32)
#define T_64(inf) (inf->types == TYPE_64)

#define SH_ADDR(inf, x) (T_64(inf) ?\
inf->shdr64[x].sh_addr : inf->shdr32[x].sh_addr)

#define SH_NAME(inf, x) (T_64(inf) ?\
inf->shdr64[x].sh_name : inf->shdr32[x].sh_name)

#define SH_SIZE(inf, x) (T_64(inf) ?\
inf->shdr64[x].sh_size : inf->shdr32[x].sh_size)

#define SH_TYPE(inf, x) (T_64(inf) ?\
inf->shdr64[x].sh_type : inf->shdr32[x].sh_type)

#define SH_FLAGS(inf, x) (T_64(inf) ?\
inf->shdr64[x].sh_flags : inf->shdr32[x].sh_flags)

#define SH_OFFSET(inf, x) (T_64(inf) ?\
inf->shdr64[x].sh_offset : inf->shdr32[x].sh_offset)


#define E_ENTRY(inf) (T_64(inf) ? inf->ehdr64->e_entry : inf->ehdr32->e_entry)
#define E_FLAGS(inf) (T_64(inf) ? inf->ehdr64->e_flags : inf->ehdr32->e_flags)
#define E_SHNUM(inf) (T_64(inf) ? inf->ehdr64->e_shnum : inf->ehdr32->e_shnum)
#define E_SHOFF(inf) (T_64(inf) ? inf->ehdr64->e_shoff : inf->ehdr32->e_shoff)
#define E_TYPE(inf) (T_64(inf) ? inf->ehdr64->e_type : inf->ehdr32->e_type)
#define E_MACHINE(inf) (T_64(inf) ?\
inf->ehdr64->e_machine : inf->ehdr32->e_machine)

#define E_SHSTRNDX(inf) (T_64(inf) ?\
inf->ehdr64->e_shstrndx : inf->ehdr32->e_shstrndx)


#define ST_NAME(inf, x) (T_64(inf) ?\
inf->sym64[x].st_name : inf->sym32[x].st_name)

#define ST_INFO(inf, x) (T_64(inf) ?\
inf->sym64[x].st_value : inf->sym32[x].st_info)

#define ST_SHNDX(inf, x) (T_64(inf) ?\
inf->sym64[x].st_shndx : inf->sym32[x].st_shndx)

#define ST_VALUE(inf, x) (T_64(inf) ?\
inf->sym64[x].st_value : inf->sym32[x].st_value)

#define BIND_ST_INFO(inf, x) (T_64(inf) ?\
ELF64_ST_BIND(inf->sym64[x].st_info) : ELF32_ST_BIND(inf->sym32[x].st_info))

#define TYPE_ST_INFO(inf, x) (T_64(inf) ?\
ELF64_ST_TYPE(inf->sym64[x].st_info) : ELF32_ST_TYPE(inf->sym32[x].st_info))


#define CONTENT_64 ((char *)infos->ehdr64 + \
infos->shdr64[infos->ehdr64->e_shstrndx].sh_offset)
#define CONTENT_32 ((char *)infos->ehdr32 + \
infos->shdr32[infos->ehdr32->e_shstrndx].sh_offset)

typedef enum types_s
{
    TYPE_32 = 0,
    TYPE_64 = 1
} type_t;

typedef struct elf_info_s
{
    void *infos;
    char *strtab;
    char *p;

    type_t types;

    int sym_shift;
    int str_shift;

    const char *file_name;
    unsigned int file_size;

    Elf32_Sym *sym32;
    Elf64_Sym *sym64;
    Elf32_Shdr *shdr32;
    Elf64_Shdr *shdr64;
    Elf32_Ehdr *ehdr32;
    Elf64_Ehdr *ehdr64;
} elf_info_t;

#endif