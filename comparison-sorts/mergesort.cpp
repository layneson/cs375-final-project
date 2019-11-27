#include <iostream>
#include <chrono>
#include <fstream>
#include <random>
using namespace std;
using namespace std::chrono;


// A function to merge the two half into a sorted data.
void Merge(int *a, int low, int high, int mid)
{
	// We have low to mid and mid+1 to high already sorted.
	int i, j, k, temp[high-low+1];
	i = low;
	k = 0;
	j = mid + 1;

	// Merge the two parts into temp[].
	while (i <= mid && j <= high)
	{
		if (a[i] < a[j])
		{
			temp[k] = a[i];
			k++;
			i++;
		}
		else
		{
			temp[k] = a[j];
			k++;
			j++;
		}
	}

	// Insert all the remaining values from i to mid into temp[].
	while (i <= mid)
	{
		temp[k] = a[i];
		k++;
		i++;
	}

	// Insert all the remaining values from j to high into temp[].
	while (j <= high)
	{
		temp[k] = a[j];
		k++;
		j++;
	}


	// Assign sorted data stored in temp[] to a[].
	for (i = low; i <= high; i++)
	{
		a[i] = temp[i-low];
	}
}

// A function to split array into two parts.
void MergeSort(int *a, int low, int high)
{
	int mid;
	if (low < high)
	{
		mid=(low+high)/2;
		// Split the data into two half.
		MergeSort(a, low, mid);
		MergeSort(a, mid+1, high);

		// Merge them to get sorted output.
		Merge(a, low, high, mid);
	}
}

/*timing and running mergesort on the array*/
int timeMergeSort(int arr[], int n) {
	auto start = high_resolution_clock::now();
	MergeSort(arr, 0, n);
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(end - start);
	return duration.count();
}

int main(int argv, char** args)
{
  ofstream outputFile;
  outputFile.open(args[1]);
	outputFile << "x,y" << endl;

/***ALL TESTING VARIABLES HERE***/
  int numOfTests = 5000;
  int maxSizeOfArray = 1500;
  int minSizeOfArray = 1;
  int maxElementValue = 20;
	int minElementValue = 1;
	bool sortedTest = false; //runs different part of test to strictly load sorted case examples
	bool revSortedTest = false; //can be run cocurrently with sorted scenario
/** END TESTING VARIABLES **/

	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<> distr_size(minSizeOfArray, maxSizeOfArray);
	uniform_int_distribution<> distr_elem(minElementValue, maxElementValue);
  /*creates, sorts, times, and outputs data for 100 arrays ranging in size from 1 to 10, with data values ranging from 1 to 20*/

	// worstCase runs creates sorted array, best case runs reverse sorted
	if (sortedTest || revSortedTest) {
		if(sortedTest) {
			for (int j = 1; j <= maxSizeOfArray; j++) {
				int arr[j];
				for (int i = 0; i < j; i++) {
					arr[i] = i;
				}
				int runningtime = timeMergeSort(arr, j);
				outputFile << j << ',' << runningtime <<endl;
			}
		}
		if(revSortedTest) {
			for (int j = 0; j < maxSizeOfArray; j++) {
				int arr[j];
				for (int i = 0; i <= j; i++) {
					arr[i] = j-i;
				}
				int runningtime = timeMergeSort(arr, j);
				outputFile << j << ',' << runningtime <<endl;
			}
		}
	}
	else {
		for (int i = 0; i < numOfTests; i++) {
			/*create a randomly sized arr between 1 and 10 elements*/

			int arrsize = distr_size(eng);
			int arr[arrsize];

			/*loading the array with random values between 1 and 20*/
			for(int j = 0; j < arrsize; j++) {
				arr[j] = rand() % maxElementValue + minElementValue;
			}
			/*timing and running mergesort on the array*/
			int runningtime = timeMergeSort(arr, arrsize-1);
			/*outputting as CSV format*/
			outputFile << arrsize << ',' << runningtime <<endl;
	  }
	}

	return 0;
}







//