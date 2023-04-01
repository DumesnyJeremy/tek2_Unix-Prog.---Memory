/*
** EPITECH PROJECT, 2021
** B-PSU-400-NCE-4-1-nmobjdump-jeremy.dumesny
** File description:
** my_elf.h
*/

#include <stdio.h>
#include "my_objdump.h"

int main(int ac, char **av)
{
    if (ac < 2)
        return (obj_head("a.out"));
    for (int x = 1; x < ac; x++) {
        obj_head(av[x]);
    }
}
