
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../../include/efficient_sorts.h"


#define ARRAY_MAX 1024


static void fill_random(int *a, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        a[i] = (int)rand() - RAND_MAX/2;
}

static void check_sorted(const int *a, size_t n)
{
    for (size_t i = 1; i < n; ++i)
        assert(a[i-1] <= a[i]);
}


static void test_heap_sort(void)
{
    int a[ARRAY_MAX];
    fill_random(a, ARRAY_MAX);
    heap_sort(a, ARRAY_MAX);
    check_sorted(a, ARRAY_MAX);
    puts("[OK] heap_sort");
}


static void test_edge_cases(void)
{

    heap_sort(NULL, 0);
    quick_sort(NULL, 0, -1);
    merge_sort(NULL, 0, 1);
    timsort(NULL, 0);
    introsort(NULL, 0);
    puts("[OK] edge cases (empty)");

    int one[1] = {42};
    heap_sort(one, 1);
    quick_sort(one, 0, 0);
    merge_sort(one, 1, 1);
    timsort(one, 1);
    introsort(one, 1);
    check_sorted(one, 1);
    puts("[OK] edge cases (single element)");

    int sorted[10] = {0,1,2,3,4,5,6,7,8,9};
    heap_sort(sorted, 10);
    quick_sort(sorted, 0, 9);
    merge_sort(sorted, 10, 1);
    timsort(sorted, 10);
    introsort(sorted, 10);
    check_sorted(sorted, 10);
    puts("[OK] edge cases (already sorted)");
}

