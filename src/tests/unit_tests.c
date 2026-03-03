#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/efficient_sorts.h"

void test_heap_sort(void);
void test_quick_sort(void);
void test_merge_sort(void);
void test_timsort(void);
void test_introsort(void);
void test_edge_cases(void);
void test_stress_small(void);

int main(void)
{
  srand((unsigned)time(NULL));

  test_heap_sort();
  test_quick_sort();
  test_merge_sort();
  test_timsort();
  test_introsort();
  test_edge_cases();
  test_stress_small();

  printf("\nВсе тесты пройдены успешно!\n");
  return EXIT_SUCCESS;
}
