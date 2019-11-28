#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <math.h>

#include <random>
#include <chrono>

#include "radixsort.hpp"
#include "quicksort.hpp"
#include "mergesort.hpp"

enum Mode {
    RANDOM,
    SORTED,
    REVERSE_SORTED
};

int main(int argc, char** argv) {
    if (argc < 7) {
        fprintf(stderr, "[!] Args: <seed> <mode (random, sorted, reverse_sorted)> <max array size> <array size step> <max num> <max radix>\n");
        return 1;
    }

    int seed = atoi(argv[1]);

    Mode mode;
    if (strcmp(argv[2], "random") == 0) {
        mode = RANDOM;
    } else if (strcmp(argv[2], "sorted") == 0) {
        mode = SORTED;
    } else if (strcmp(argv[2], "reverse_sorted") == 0) {
        mode = REVERSE_SORTED;
    } else {
        fprintf(stderr, "[!] Unknown mode '%s' (must be one of 'random', 'sorted', or 'reverse_sorted'!\n", argv[2]);
        return 1;
    }

    int max_array_size = atoi(argv[3]);
    int array_size_step = atoi(argv[4]);
    int max_num = atoi(argv[5]);
    int max_radix = atoi(argv[6]);

    FILE* merge_output = fopen("output/merge.csv", "w");
    FILE* quick_output = fopen("output/quick.csv", "w");
    FILE* radix_output = fopen("output/radix.csv", "w");
    if (!merge_output || !quick_output || !radix_output) {
        fprintf(stderr, "[!] Failed to open output file!\n");
        return 1;
    }

    fprintf(merge_output, "n,t\n");
    fprintf(quick_output, "n,t\n");
    fprintf(radix_output, "r,n,t\n");

    std::default_random_engine rand_eng(seed);
    std::uniform_int_distribution<int> rng(0, max_num-1);

    for (int n = array_size_step; n <= max_array_size; n += array_size_step) {
        int* base_array = (int*) malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            base_array[i] = rng(rand_eng);
        }

        int* secondary_array = (int*) malloc(n * sizeof(int));

        printf("\rn = %d / %d", n, max_array_size);
        fflush(stdout);

        auto start = std::chrono::high_resolution_clock::now();
        memcpy(secondary_array, base_array, n * sizeof(int));
        Quicksort(secondary_array, 0, n-1);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        fprintf(quick_output, "%d,%ld\n", n, duration);

        start = std::chrono::high_resolution_clock::now();
        memcpy(secondary_array, base_array, n * sizeof(int));
        MergeSort(secondary_array, 0, n-1);
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        fprintf(merge_output, "%d,%ld\n", n, duration);

        for (int r = 2; r <= max_radix; r++) {
            SortingItem* radix_array = (SortingItem*) malloc(n * sizeof(SortingItem));
            for (int i = 0; i < n; i++) {
                radix_array[i].value = base_array[i];
            }

            start = std::chrono::high_resolution_clock::now();
            radix_sort(radix_array, n, max_num, r);
            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            fprintf(radix_output, "%d,%d,%ld\n", r, n, duration);

            free(radix_array);
        }

        free(base_array);
        free(secondary_array);
    }

    fclose(merge_output);
    fclose(quick_output);
    fclose(radix_output);

    printf("\n");

    return 0;
}
