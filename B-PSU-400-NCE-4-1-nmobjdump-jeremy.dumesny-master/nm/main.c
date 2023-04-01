/*
** EPITECH PROJECT, 2021
** B-PSU-400-NCE-4-1-nmobjdump-jeremy.dumesny
** File description:
** my_elf.h
*/

#include "my_nm.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

int main(int ac, char **av)
{
    if (ac < 2)
        return (nm_head("a.out", 1, ac));
    for (int x = 1; x < ac; x++) {
        nm_head(av[x], x, ac);
    }
}