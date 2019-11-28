#include <iostream>
#include <chrono>
#include <fstream>
#include <random>

using namespace std;
using namespace std::chrono;

void Merge(int *a, int left, int right, int mid) {
	int i = left;
	int x = 0;
	int j = mid + 1;
	int temparr[right-left+1];

	while (i <= mid && j <= right) {
		temparr[x] = (a[i] < a[j]) ? a[i] : a[j];
		x++;
		if (a[i] < a[j]) i++;
		else j++;
	}

	/*fill in remaining values*/
	while (i <= mid) {
		temparr[x] = a[i];
		x++;
		i++;
	}
	while (j <= right) {
		temparr[x] = a[j];
		x++;
		j++;
	}

	//copy back over to a
	for (i = left; i <= right; i++) {
		a[i] = temparr[i-left];
	}
}

void MergeSort(int *a, int left, int right) {
	int mid;
	if (left < right) {
		mid = (left+right)/2;
		MergeSort(a, left, mid);
		MergeSort(a, mid+1, right);
		Merge(a, left, right, mid);
	}
}

