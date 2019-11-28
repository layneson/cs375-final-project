#include <stdlib.h>

size_t memory_usage = 0;

void* measure_malloc(size_t size) {
    memory_usage += size;

    return malloc(size);
}

void clear_memory_usage() {
    memory_usage = 0;
}

size_t get_memory_usage() {
    return memory_usage;
}
