#ifndef SIMPLESORTS_H
#define SIMPLESORTS_H
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* support functions */
void swap_bytes(void *a, void *b, size_t size, long *swaps);
void* elem(void *base, int index, size_t size);

/* simple sorts */
void insertion_sort(void *arr, int n, size_t size, int (*cmp)(const void*, const void*), long *comparisons, long *swaps);
void selection_sort(void *arr, int n, size_t size, int (*cmp)(const void*, const void*), long *comparisons, long *swaps);
void bubble_sort(void *arr, int n, size_t size, int (*cmp)(const void*, const void*), long *comparisons, long *swaps);

/* recursive functions */
void gnome_sort(void *arr, int n, size_t size, int (*cmp)(const void*, const void*), long *comparisons, long *swaps);
void stooge_sort(void *arr, int left, int right, size_t size, int (*cmp)(const void*, const void*), long *comparisons, long *swaps);

/* shell sort */
void shell_sort(void *arr, int n, size_t size, int (*cmp)(const void*, const void*), long *comparisons, long *swaps);

#endif
