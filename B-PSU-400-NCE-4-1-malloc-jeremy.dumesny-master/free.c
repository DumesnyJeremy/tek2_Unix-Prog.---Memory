/*
** EPITECH PROJECT, 2021
** B-PSU-400-NCE-4-1-malloc-jeremy.dumesny
** File description:
** Free
*/

#include "malloc.h"

int free_node(malloc_t *ptr)
{
    if (ptr == NULL)
        return 0;
    malloc_t *tempo = NULL;
    if (ptr->next)
        return free_node(ptr->next);
    else if (ptr->used == 0) {
        if (ptr == actu_malloc)
            actu_malloc = NULL;
        tempo = actu_malloc;
        while (tempo) {
            if (tempo->next && tempo->next == ptr) {
                tempo->next = NULL;
                break;
            }
            tempo = tempo->next;
        }
        brk(ptr);
        return 1;
    }
    return 0;
}

void free(void *ptr)
{
    if (!ptr)
        return;
    ((malloc_t *)(ptr - sizeof(malloc_t)))->used = 0;
    while (free_node(actu_malloc) == 1);
}
