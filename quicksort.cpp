#include <stdio.h>

void swap(int*a , int first, int second) {
	int t = a[first];
	a[first] = a[second];
	a[second] = t;
}

int partition(int *a, int left, int right) {
    int pivot = a[right];

    int curr_index = left;
    int i;

    for(i = left; i < right; i++) {
    	if(a[i] <= pivot) {
            swap(a,i,curr_index);
            curr_index++;
        }
     }

		 swap(a,right,curr_index);

     return curr_index;
 }

 void Quicksort(int *a,int left,int right) {
    if(left < right) {
         int curr_index = partition(a,left,right);
         Quicksort(a,left, curr_index-1);
         Quicksort(a,curr_index+1, right);
    }
}
