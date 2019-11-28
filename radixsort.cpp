#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "radixsort.hpp"
#include "memory.hpp"

void counting_sort(SortingItem* array, int n, int k) {
    SortingItem* b = (SortingItem*) measure_malloc(n * sizeof(SortingItem));
    int* c = (int*) measure_malloc(k * sizeof(int));

    for (int i = 0; i < k; i++) {
        c[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        c[array[i].key]++;
    }

    for (int i = 1; i < k; i++) {
        c[i] += c[i-1];
    }

    for (int i = n - 1; i >= 0; i--) {
        b[c[array[i].key] - 1] = array[i];
        c[array[i].key]--;
    }

    memcpy(array, b, n * sizeof(SortingItem));

    free(b);
    free(c);
}

void radix_sort(SortingItem* array, int n, int max, int radix) {
    int num_digits = (int) (logf(max)/logf(radix)) + 1;

    for (int d = 0; d < num_digits; d++) {
        int denom = radix;

        for (int i = 0; i < n; i++) {
            array[i].key = (array[i].value / denom) % radix;
        }

        denom *= radix;

        counting_sort(array, n, radix);
    }
}
