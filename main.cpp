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
#include "memory.hpp"

enum Mode {
    RANDOM,
    SORTED,
    REVERSE_SORTED
};

void gen_array(std::mt19937 eng, std::uniform_int_distribution<int> dist, Mode mode, int* array, int n, int max_num) {
    switch (mode) {
        case RANDOM: {
            for (int i = 0; i < n; i++) {
                array[i] = dist(eng);
            }
            break;
        } case SORTED: {
            int base = dist(eng);
            if (base + n >= max_num) base = base % max_num;

            for (int i = 0; i < n; i++) {
                array[i] = base + i;
            }
            break;
        } case REVERSE_SORTED: {
            int base = dist(eng);
            if (base + n >= max_num) base = base % max_num;

            for (int i = 0; i < n; i++) {
                array[i] = base + n - 1 - i;
            }
            break;
        }
    }
}

enum RepMode {
    SAME,
    NEW
};

int main(int argc, char** argv) {
    if (argc < 9) {
        fprintf(stderr, "[!] Args: <seed> <gen mode (random, sorted, reverse_sorted)> <max array size> <array size step> <repetitions> <rep mode> <max num> <max radix>\n");
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
        fprintf(stderr, "[!] Unknown gen mode '%s' (must be one of 'random', 'sorted', or 'reverse_sorted')!\n", argv[2]);
        return 1;
    }

    int max_array_size = atoi(argv[3]);
    int array_size_step = atoi(argv[4]);
    int repetitions = atoi(argv[5]);

    RepMode rep_mode;
    if (strcmp(argv[6], "same") == 0) {
        rep_mode = SAME;
    } else if (strcmp(argv[6], "new") == 0) {
        rep_mode = NEW;
    } else {
        fprintf(stderr, "[!] Unknown rep mode '%s' (must be one of 'same' or 'new')!\n", argv[6]);
    }

    int max_num = atoi(argv[7]);
    int max_radix = atoi(argv[8]);

    FILE* merge_output = fopen("output/merge.csv", "w");
    FILE* quick_output = fopen("output/quick.csv", "w");
    FILE* radix_output = fopen("output/radix.csv", "w");
    if (!merge_output || !quick_output || !radix_output) {
        fprintf(stderr, "[!] Failed to open output file!\n");
        return 1;
    }

    fprintf(merge_output, "n,t,m\n");
    fprintf(quick_output, "n,t,m\n");
    fprintf(radix_output, "r,n,t,m\n");

    std::mt19937 rand_eng(seed);
    std::uniform_int_distribution<int> rng(0, max_num-1);

    for (int n = array_size_step; n <= max_array_size; n += array_size_step) {
        int* base_array = (int*) malloc(n * sizeof(int));
        gen_array(rand_eng, rng, mode, base_array, n, max_num);

        int* secondary_array = (int*) malloc(n * sizeof(int));

        printf("\rn = %d / %d", n, max_array_size);
        fflush(stdout);

        for (int i = 0; i < repetitions; i++) {
            clear_memory_usage();

            if (rep_mode == NEW) gen_array(rand_eng, rng, mode, base_array, n, max_num);
            memcpy(secondary_array, base_array, n * sizeof(int));

            auto start = std::chrono::high_resolution_clock::now();
            Quicksort(secondary_array, 0, n-1);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            fprintf(quick_output, "%d,%ld,%lu\n", n, duration, get_memory_usage());
        }


        for (int i = 0; i < repetitions; i++) {
            clear_memory_usage();

            if (rep_mode == NEW) gen_array(rand_eng, rng, mode, base_array, n, max_num);
            memcpy(secondary_array, base_array, n * sizeof(int));

            auto start = std::chrono::high_resolution_clock::now();
            MergeSort(secondary_array, 0, n-1);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            fprintf(merge_output, "%d,%ld,%lu\n", n, duration, get_memory_usage());
        }


        for (int r = 2; r <= max_radix; r++) {
            SortingItem* radix_array = (SortingItem*) malloc(n * sizeof(SortingItem));

            for (int i = 0; i < repetitions; i++) {
                clear_memory_usage();

                if (rep_mode == NEW) gen_array(rand_eng, rng, mode, base_array, n, max_num);
                for (int j = 0; j < n; j++) {
                    radix_array[j].value = base_array[j];
                }

                auto start = std::chrono::high_resolution_clock::now();
                radix_sort(radix_array, n, max_num, r);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

                fprintf(radix_output, "%d,%d,%ld,%lu\n", r, n, duration, get_memory_usage());
            }

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
