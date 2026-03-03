#include "sorting.h"
#include <stdio.h>

int main() {
  int arr[] = {64, 34, 25, 12, 22, 11, 90};
  int n = sizeof(arr)/sizeof(arr[0]);

  printf("Original array: ");

  // Используем функции из модуля efficient_sorts.h
  quick_sort(arr, 0, n-1);
  printf("Quick sorted: ");


  return 0;
}