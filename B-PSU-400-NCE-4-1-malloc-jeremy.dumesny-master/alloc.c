/*
** EPITECH PROJECT, 2021
** B-PSU-400-NCE-4-1-malloc-jeremy.dumesny
** File description:
** Malloc
*/

#include "malloc.h"

malloc_t *actu_malloc = NULL;

void *malloc(size_t size)
{
    if (size <= 0)
        return NULL;
    void *malloc = NULL;
    size_t alloc_size = 0;
    alloc_size = get_size_to_alloc(sizeof(malloc_t) + size);
    malloc_t *ptr = actu_malloc;
    while (ptr != NULL) {
        if (ptr->used == 0 && ptr->size >= size)
            malloc =  ptr;
        ptr = ptr->next;
    }
    malloc = NULL;
    if (malloc == NULL) {
        malloc = sbrk(alloc_size);
        create_malloc(malloc, alloc_size);
    } else {
        ((malloc_t *)malloc)->used = 1;
    }
    return (malloc + sizeof(malloc_t));
}

void *realloc(void *ptr, size_t size)
{
    if (size == 0) {
        free(ptr);
        return NULL;
    }
    void *realloc = NULL;
    size_t alloc_size = 0;
    alloc_size = get_size_to_alloc(sizeof(malloc_t) + size);

    if (ptr && ((malloc_t *)(ptr - sizeof(malloc_t)))->size >= alloc_size)
        return ptr;
    realloc = malloc(size);
    if (ptr != NULL) {
        size_t malloc_size = ((malloc_t *)(ptr - sizeof(malloc_t)))->size - sizeof(malloc_t);
        if (malloc_size < size)
            memcpy(realloc, ptr, malloc_size);
        else
            memcpy(realloc, ptr, size);
        free(ptr);
    }
    return realloc;
}

void *calloc(size_t nmemb, size_t size)
{
    unsigned char *ptr;
    size_t pos;

    if ((ptr = malloc(size * nmemb)) == NULL)
        return (NULL);
    pos = 0;
    while (pos < size) {
        ptr[pos] = 0;
        ++pos;
        }
    return ptr;
}