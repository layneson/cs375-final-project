/* C++ implementation of QuickSort */
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <fstream>
#include <random>

using namespace std;
using namespace std::chrono;


int partition(int *a,int start,int end)
{
    int pivot=a[end];
    //P-index indicates the pivot value index

    int P_index=start;
    int i,t; //t is temporary variable

    //Here we will check if array value is
    //less than pivot
    //then we will place it at left side
    //by swapping

    for(i=start;i<end;i++)
    {
    	if(a[i]<=pivot)
        {
            t=a[i];
            a[i]=a[P_index];
            a[P_index]=t;
            P_index++;
        }
     }
     //Now exchanging value of
     //pivot and P-index
      t=a[end];
      a[end]=a[P_index];
      a[P_index]=t;

     //at last returning the pivot value index
     return P_index;
 }
 void Quicksort(int *a,int start,int end)
 {
    if(start<end)
    {
         int P_index=partition(a,start,end);
             Quicksort(a,start,P_index-1);
             Quicksort(a,P_index+1,end);
    }
}


/*timing and running mergesort on the array*/
int timeQuickSort(int arr[], int n) {
	auto start = high_resolution_clock::now();
	Quicksort(arr, 0, n);
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
				int runningtime = timeQuickSort(arr, j);
				outputFile << j << ',' << runningtime <<endl;
			}
		}
		if(revSortedTest) {
			for (int j = 0; j < maxSizeOfArray; j++) {
				int arr[j];
				for (int i = 0; i <= j; i++) {
					arr[i] = j-i;
				}
				int runningtime = timeQuickSort(arr, j);
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
			/*timing and running quicksort on the array*/
			int runningtime = timeQuickSort(arr, arrsize-1);
			/*outputting as CSV format*/
			outputFile << arrsize << ',' << runningtime <<endl;
	  }
	}

	return 0;
}

// This code is contributed by rathbhupendra
