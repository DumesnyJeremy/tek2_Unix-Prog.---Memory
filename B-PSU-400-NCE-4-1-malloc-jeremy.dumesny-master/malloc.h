/*
** EPITECH PROJECT, 2021
** B-PSU-400-NCE-4-1-malloc-jeremy.dumesny
** File description:
** Malloc
*/

#ifndef MALLOC_H_
#define MALLOC_H_

#include <pthread.h>
#include <string.h>
#include <unistd.h>



typedef struct
{
    size_t size;
    void *next;
    char used;
} malloc_t;

extern malloc_t *actu_malloc;

size_t get_size_to_alloc(size_t rew);
void create_malloc(void *malloc, size_t alloc_size);

void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void *calloc(size_t nmemb, size_t size);

int free_node(malloc_t *ptr);
void free(void *ptr);

#endif