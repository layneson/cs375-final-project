struct SortingItem {
    int key;
    int value;
};

void counting_sort(SortingItem* array, int n, int k);
void radix_sort(SortingItem* array, int n, int max, int radix);
