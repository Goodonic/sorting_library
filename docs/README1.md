# Simple Sorts Library (Role 1)

## Реализованные алгоритмы

- Insertion Sort (binary search)
- Selection Sort (двунаправленный)
- Bubble Sort (шейкерный)
- Gnome Sort
- Stooge Sort
- Shell Sort

---

## Асимптотическая сложность

| Алгоритм | Лучшая | Средняя | Худшая | Память |
|-----------|--------|---------|--------|--------|
| Insertion | O(n) | O(n²) | O(n²) | O(1) |
| Selection | O(n²) | O(n²) | O(n²) | O(1) |
| Bubble    | O(n) | O(n²) | O(n²) | O(1) |
| Gnome     | O(n) | O(n²) | O(n²) | O(1) |
| Stooge    | - | O(n^2.7) | O(n^2.7) | O(log n) |
| Shell     | ~O(n log n) | ~O(n^1.3) | O(n²) | O(1) |

---

## Особенности

- Generic реализация через void*
- Поддержка пользовательского компаратора
- Подсчёт сравнений и обменов
- Обработка граничных случаев
- Нет утечек памяти