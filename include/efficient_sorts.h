/**
* @file efficient_sorts.h
 * @brief Общий заголовочный файл проекта "efficient_sorts".
 *
 * В нём объявлены все публичные функции сортировок и вспомогательные типы.
 *
 * Алгоритмы:
 *   - quick_sort   – классический quick‑sort (Hoare‑partition)
 *   - merge_sort   – топ‑даун / боттом‑ап merge‑sort (выбор через option)
 *   - heap_sort    – сортировка кучей
 *   - timsort      – адаптивная сортировка
 *   - introsort    – гибрид quick‑/heap‑/insertion‑sort (Introsort)
 *
 * Все функции работают **на месте**, требуют только массив `int` и его размер.
 *
 * @author  Никита
 * @date    2026‑03‑03
 */
#ifndef EFFICIENT_SORTS_H
#define EFFICIENT_SORTS_H
#pragma once

#include <stddef.h>

void quick_sort(int *s_arr,  int first,  int last);

void merge_sort(int a[], size_t n, int option);

void heap_sort(int arr[], int n);;

void timsort(int a[], int n);

void introsort(int a[], int n);

static void swap(int *a, int *b)
{
  const int t = *a;
  *a = *b;
  *b = t;
}

/* -----------------------------------------------------------------
 *  Вспомогательные типы
 * ----------------------------------------------------------------- */
typedef struct {
  int start;   /**< индекс начала run */
  int len;     /**< длина run   */
} run_t;
#endif //EFFICIENT_SORTS_H
