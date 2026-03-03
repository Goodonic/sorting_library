#include "simple_sorts.h"

void swap_bytes(void *a, void *b, size_t size, long *swaps)
{
  if (a == b) return;

  unsigned char *tmp = malloc(size);
  if (!tmp) return;

  memcpy(tmp, a, size);
  memcpy(a, b, size);
  memcpy(b, tmp, size);

  free(tmp);

  if (swaps) (*swaps)++;
}

void* elem(void *base, int index, size_t size)
{
  return (char*)base + index * size;
}