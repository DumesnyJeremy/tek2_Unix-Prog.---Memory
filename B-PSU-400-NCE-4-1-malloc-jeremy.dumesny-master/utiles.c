/*
** EPITECH PROJECT, 2021
** B-PSU-400-NCE-4-1-malloc-jeremy.dumesny
** File description:
** Utiles
*/

#include "malloc.h"

void create_malloc(void *malloc, size_t alloc_size)
{
    malloc_t *node = NULL, *tempo = NULL;
    node = malloc;
    node->used = 1;
    node->next = NULL;
    node->size = alloc_size;

    if (actu_malloc != NULL) {
        tempo = actu_malloc;
        while (tempo->next) {
            tempo = tempo->next;
        }
        tempo->next = node;
    } else {
        actu_malloc = node;
    }
}

size_t get_size_to_alloc(size_t rew)
{
    size_t i;
    static int page = 0;

    if (page == 0)
        page = getpagesize();
    i = page * 2;
    while (i < rew)
        i += page * 2;
    return i;
}