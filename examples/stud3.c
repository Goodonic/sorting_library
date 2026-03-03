#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swap(int* a, int* b) {                                           // Swap two integers
    int n1 = *a;                                                      // Store a
    *a = *b;                                                          // Assign b to a
    *b = n1;                                                          // Assign stored to b
}

void counting_sort(int* arr, int n, int min_val, int max_val) {       // Counting sort
    int len = max_val - min_val + 1;                                  // Range length
    int* range = (int*)malloc(len * sizeof(int));                     // Value range array
    int* freq = (int*)calloc(len, sizeof(int));                       // Frequency array
    int c = min_val;                                                  // Counter for range
    int i, j, k = 0;                                                  // Loop indices

    for (i = 0; c <= max_val; i++) {                                  // Fill range
        *(range + i) = c;                                             // Store value
        c++;
    }

    for (i = 0; i < n; i++)                                           // Count frequencies
        for (j = 0; j < len; j++)
            if (arr[i] == *(range + j))
                (*(freq + j))++;

    for (i = 0; i < len; i++)                                         // Reconstruct sorted array
        for (j = 0; j < *(freq + i); j++) {
            *(arr + k) = *(range + i);
            k++;
        }

    for (i = 0; i < n; i++)                                           // Print sorted
        printf("%d ", *(arr + i));
    printf("\n");

    free(range);                                                      // Cleanup
    free(freq);
}

int intmin(int* arr, int n) {                                         // Find minimum
    int min = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] < min)
            min = arr[i];
    return min;
}

int intmax(int* arr, int n) {                                         // Find maximum
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void radix_sort_lsd(int* arr, int n) {                                // LSD radix sort
    int* sort = (int*)malloc(n * sizeof(int));                        // Temp array
    int max_digits = 0;
    int min = intmin(arr, n);                                         // Shift to non‑negative
    int i;

    for (int i = 0; i < n; i++)                                       // Apply shift
        arr[i] -= min;

    int max = intmax(arr, n);                                         // New max after shift
    while (max > 0) {                                                 // Count digits
        max /= 10;
        max_digits++;
    }

    for (int digit = 0; digit < max_digits; digit++) {                // Process each digit
        int* count = (int*)calloc(10, sizeof(int));                   // Count array
        for (i = 0; i < n; i++) {
            int d = (arr[i] / (int)pow(10, digit)) % 10;              // Extract digit
            (*(count + d))++;
        }

        for (i = 1; i < 10; i++)                                      // Cumulative counts
            *(count + i) += *(count + i - 1);

        for (i = n - 1; i >= 0; i--) {                                // Build sorted order
            int d = (arr[i] / (int)pow(10, digit)) % 10;
            int pos = *(count + d) - 1;
            *(sort + pos) = arr[i];
            (*(count + d))--;
        }

        for (i = 0; i < n; i++)                                       // Copy back
            arr[i] = *(sort + i);

        free(count);
    }

    for (int i = 0; i < n; i++)                                       // Restore original
        *(arr + i) += min;

    for (i = 0; i < n; i++)                                           // Print result
        printf("%d\n", arr[i]);

    free(sort);
}

void dutch_flag_sort(int* arr, int n) {                               // 0,1,2 sort
    int mid = 0, low = 0, high = n - 1;                                 // Three pointers
    while (mid <= high) {
        if (arr[mid] == 0) {                                          // 0 → swap to low
            swap(&arr[low], &arr[mid]);
            low++; mid++;
        }
        else if (arr[mid] == 2) {                                     // 2 → swap to high
            swap(&arr[high], &arr[mid]);
            high--;
        }
        else if (arr[mid] == 1)                                       // 1 → leave
            mid++;
    }
    for (int i = 0; i < n; i++)                                       // Output
        printf("%d ", arr[i]);
}

void general_dutch_flag_sort(int* arr, int n, int k) {                // k‑way partition
    int i;
    int* pos = (int*)malloc(k * sizeof(int));                         // Start positions
    int* next = (int*)malloc(k * sizeof(int));                        // Next free slot
    pos[0] = 0;
    int* count = (int*)calloc(k, sizeof(int));                        // Colour counts
    for (i = 0; i <= n - 1; i++)
        count[arr[i]] += 1;

    for (i = 1; i <= k - 1; i++)                                      // Compute starts
        pos[i] = pos[i - 1] + count[i - 1];

    for (int j = 0; j < k; ++j)                                       // Init next pointers
        next[j] = pos[j];

    i = 0;
    while (i < n) {                                                   // Main loop
        int value = arr[i];
        if (i >= pos[value] && i < pos[value] + count[value])         // Already in place
            i = i + 1;
        else {                                                         // Swap to correct block
            swap(&arr[i], &arr[next[value]]);
            next[value] = next[value] + 1;
        }
    }
    for (int i = 0; i < n; i++)                                       // Print sorted
        printf("%d ", arr[i]);
    free(pos); free(count); free(next);
}

void merge(int* mas1, int* mas2, int* arr, int t1, int t2) {          // Merge two sorted arrays
    int i = 0, j = 0, g = 0;
    while (i < t1 && j < t2) {                                        // Compare and merge
        if (mas1[i] <= mas2[j])
            arr[g++] = mas1[i++];
        else
            arr[g++] = mas2[j++];
    }
    while (i < t1) arr[g++] = mas1[i++];                              // Copy leftovers
    while (j < t2) arr[g++] = mas2[j++];
}

void k_way_merge(int* arr, int n) {                                   // Recursive merge sort
    int t;
    if (n == 1) return;
    if (n % 2 == 0) t = n / 2;                                        // Split point
    else t = (n - 1) / 2;

    int* mas1 = (int*)calloc(t, sizeof(int));                         // Left subarray
    int* mas2 = (int*)calloc(t, sizeof(int));                         // Right subarray (should be n-t)

    for (int i = 0; i < t; i++) mas1[i] = arr[i];                     // Copy left part
    for (int i = t; i < n; i++) mas2[i - t] = arr[i];                 // Copy right part

    k_way_merge(mas1, t);                                             // Sort left
    k_way_merge(mas2, n - t);                                         // Sort right
    merge(mas1, mas2, arr, t, n - t);                                 // Merge into original

    free(mas1); free(mas2);
}

//TESTS
int main() {
    int n1 = 11;
    int n2 = 20;
    int n3 = 15;
    int n4 = 4;
    int n5 = 3;
    int k = 134135;
    int min_val = -2;
    int max_val = 3;
    int arr1[] = { 2, 3, -2, 0, 0, 1, 1, 2, -1, 1, 0 };
    int arr2[] = { 0, 1, 2, 0, 0, 0, 2, 1, 2, 2, 0, 1, 0, 0, 1, 1, 1, 2, 2, 1 };
    int arr3[] = { 1, 4, 2, 6, 2, 1, 10, 1, 23, 5, 78, 3, 1234, 134134, 12 };
    int arr4[] = { 124134, -1231231, 123, -999999999 };
    int arr5[] = { 1, 4, 1 };
    counting_sort(arr1, n1, min_val, max_val);
    printf("\n");
    dutch_flag_sort(arr2, n2);
    printf("\n");
    general_dutch_flag_sort(arr3, n3, k);
    printf("\n");
    radix_sort_lsd(arr4, n4);
    printf("\n");
    k_way_merge(arr5, n5);

}