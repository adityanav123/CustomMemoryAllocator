#ifndef MEMORYALLOCATE_H_
#define MEMORYALLOCATE_H_

#include <bits/pthreadtypes.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <threads.h>

// Lock for thread safety
extern mtx_t lock_memory;

// Type definitions
typedef char ALIGN[16];
typedef union header {
    struct {
        size_t size;
        unsigned is_free;
        union header *next;
    } s;
    ALIGN stub;
} header_t;

// Keeping track of memory allocated
extern header_t *memHead;
extern header_t *memTail;

// Function declarations
header_t *getFreeBlock(size_t size);
void *customMalloc(size_t size);
void customFree(void *block);
void *customCalloc(size_t num, size_t size);
void *customRealloc(void *ptr, size_t newSize);

#endif // MEMORYALLOCATE_H_
