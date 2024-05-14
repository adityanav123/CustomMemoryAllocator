#include "MemoryAllocate.h"

// extern in MemoryAllocate.h
mtx_t lock_memory;
header_t *memHead;
header_t *memTail;

header_t *getFreeBlock(size_t size) {
  header_t *curr = memHead;
  while (curr) {
    if (curr->s.is_free && curr->s.size >= size) {
      return curr;
    }
    curr = curr->s.next;
  }
  return NULL;
}

void *customMalloc(size_t size) {
  size_t totalSize;
  void *block;
  header_t *header;

  // check if empty allocation is there
  if (!size) {
    return NULL;
  }

  totalSize = size + sizeof(header_t);

  // lock memory
  mtx_lock(&lock_memory);

  // get free block
  header = getFreeBlock(size);
  if (header) {
    header->s.is_free = 0;
    mtx_unlock(&lock_memory);
    return (void *)(header + 1);
  }

  // allocate memory
  block =
      mmap(0, totalSize, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
  if (block == MAP_FAILED) {
    mtx_unlock(&lock_memory);
    return NULL;
  }

  header = (header_t *)block;
  header->s.size = size;
  header->s.is_free = 0;
  header->s.next = NULL;

  if (!memHead) {
    memHead = header;
  }

  if (memTail) {
    memTail->s.next = header;
  }

  // unlock the memory
  mtx_unlock(&lock_memory);
  return (void *)(header + 1);
}

void customFree(void *block) {
  header_t *header;

  // check if its already NULL
  if (!block) {
    return;
  }

  // lock the memory
  mtx_lock(&lock_memory);

  // go back to the starting of header
  header = (header_t *)block - 1;

  // free the block
  header->s.is_free = 1;

  // check ptr
  if (memHead == NULL) {
    memHead = memTail = header;
    header->s.next = NULL;
  } else {
    header->s.next = memHead;
    memHead = header;
  }

  if (header->s.next == NULL) {
    memTail = header;
  }
  mtx_unlock(&lock_memory);
}

void *customCalloc(size_t num, size_t size) {
  size_t total_size = num * size;
  // allocate
  void *block = customMalloc(total_size);

  if (block != NULL) {
    memset(block, 0, total_size);
  }
  return block;
}

void *customRealloc(void *ptr, size_t newSize) {
  if (ptr == NULL) {
    return customMalloc(newSize);
  }

  if (newSize == 0) {
    customFree(ptr);
    return NULL;
  }

  // get the header
  header_t *header = (header_t *)ptr - 1;
  size_t oldSize = header->s.size;

  if (oldSize >= newSize) {
    return ptr;
  }

  void *newPtr = customMalloc(newSize);
  if (newPtr == NULL) {
    return NULL;
  }

  // copy the data
  memcpy(newPtr, ptr, oldSize);
  customFree(ptr); // free up the old ptr

  return newPtr;
}