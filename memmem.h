#ifndef MEMMEM_H
#define MEMMEM_H

#include <stddef.h>

void *memmem(void *haystack, size_t haystack_len, const void * const needle, const size_t needle_len);

#endif
