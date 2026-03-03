#include "efficient_sorts.h"

int n, a[n];
void quick_sort(int *s_arr, const int first, const int last)
{
  if (first < last)
  {
    int left = first, right = last;
    const int middle = s_arr[(left + right) / 2];
    do
    {
      while (s_arr[left] < middle) left++;
      while (s_arr[right] > middle) right--;
      if (left <= right)
      {
        int tmp = s_arr[left];
        s_arr[left] = s_arr[right];
        s_arr[right] = tmp;
        left++;
        right--;
      }
    } while (left <= right);
    quick_sort(s_arr, first, right);
    quick_sort(s_arr, left, last);
  }
}