#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <math.h>

#include <random>

typedef struct {
    int key;
    int value;
} SortingItem;

void counting_sort(SortingItem* array, int n, int k) {
    SortingItem* b = (SortingItem*) malloc(n * sizeof(SortingItem));
    int* c = (int*) malloc(k * sizeof(int));

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
    int max_bits = 32;//(int) (logf(max)/logf(2)) + 1;
    int num_digits = max_bits / radix;

    for (int d = 0; d < num_digits; d++) {
        int offset = d * radix;

        for (int i = 0; i < n; i++) {
            array[i].key = (array[i].value >> offset) % (1 << radix);
        }

        counting_sort(array, n, 1 << radix);
    }
}

int main(int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "[!] Args: <seed>, <statfile>\n");
        return 1;
    }

    int max_array_size = 100000;
    int array_size_step = 1000;
    int k = 10000;
    int max_radix = 16;

    std::default_random_engine rand_eng(atoi(argv[1]));
    std::uniform_int_distribution<int> rng(0, k-1);

    FILE* statfile = fopen(argv[2], "w");
    if (!statfile) {
        fprintf(stderr, "[!] Failed to open output file!\n");
        return 1;
    }

    struct timespec timespec;

    for (int n = 1; n < max_array_size; n += array_size_step) {
        SortingItem* array = (SortingItem*) malloc(n * sizeof(SortingItem));
        for (int i = 0; i < n; i++) {
            array[i].value = rng(rand_eng);
            //printf("%d\n", array[i].value);
        }

        printf("\r///////// n = %d", n);
        fflush(stdout);

        for (int r = 1; r < max_radix; r *= 2) {
            clock_gettime(CLOCK_MONOTONIC_RAW, &timespec);
            int start_micros = (timespec.tv_sec * 1000000) + (timespec.tv_nsec / 1000);

            for (int j = 0; j < 100; j++) {
                radix_sort(array, n, k, r);
            }

            clock_gettime(CLOCK_MONOTONIC_RAW, &timespec);
            int end_micros = (timespec.tv_sec * 1000000) + (timespec.tv_nsec / 1000);

            //printf("\t==[ Radix: %d ]==\n", r);
            for (int i = 0; i < n; i++) {
                //printf("\t\t%d\n", array[i].value);
            }

            //printf("\t(took %d micros)\n", (end_micros - start_micros)/100);

            fprintf(statfile, "%d,%d,%d\n", n, r, (end_micros - start_micros)/100);
            fflush(statfile);
        }

        free(array);
    }

    return 0;
}
