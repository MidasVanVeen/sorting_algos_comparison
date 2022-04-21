#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// forward declaration of functions
void swap(int *a, int *b);
int partition(int arr[], int low, int high);
void quickSort(int arr[], int low, int high);
void merge(int arr[], int l, int m, int r);
void mergeSort(int arr[], int l, int r);
void bubbleSort(int arr[], int n);

int main() {
	// seed
	srand(time(0));
	
	double average_times_quicksort[4];
	double average_times_bubblesort[4];
	double average_times_mergesort[4];

	for (int arrsize = 5; arrsize <= 5000; arrsize*=10) {
		double times_quicksort[20];
		double times_bubblesort[20];
		double times_mergesort[20];
		for (int iter = 0; iter < 20; iter++) {
			printf("iteration number: %2d, array size: %d\n", iter, arrsize);
			int arr[arrsize];
			for (int i = 0; i < arrsize; i++) {
				arr[i] = rand(); 
			}
			clock_t t_quicksort = clock();
			quickSort(arr, 0, sizeof(arr)/sizeof(arr[0]) - 1);
			times_quicksort[iter] = (double)(clock() - t_quicksort);

			clock_t t_bubblesort = clock();
			bubbleSort(arr, sizeof(arr)/sizeof(arr[0]));
			times_bubblesort[iter] = (double)(clock() - t_bubblesort);

			clock_t t_mergesort = clock();
			mergeSort(arr, 0, sizeof(arr)/sizeof(arr[0])-1);
			times_mergesort[iter] = (double)(clock() - t_mergesort);
		}
		double sum = 0;
		for (int i = 0; i < 20; i++) {
			sum += times_quicksort[i];
		}
		average_times_quicksort[(int)log10(arrsize/5)] = sum / 20;
		sum = 0;
		for (int i = 0; i < 20; i++) {
			sum += times_bubblesort[i];
		}
		average_times_bubblesort[(int)log10(arrsize/5)] = sum / 20;
		sum = 0;
		for (int i = 0; i < 20; i++) {
			sum += times_mergesort[i];
		}
		average_times_mergesort[(int)log10(arrsize/5)] = sum / 20;
	}
	printf("\n================================\n");
	printf("Average quicksort times: ");
	for (int i = 0; i < 4; i++) {
		printf("%f, ", average_times_quicksort[i]);
	} printf("\n");
	printf("Average bubblesort times: ");
	for (int i = 0; i < 4; i++) {
		printf("%f, ", average_times_bubblesort[i]);
	} printf("\n");
	printf("Average mergesort times: ");
	for (int i = 0; i < 4; i++) {
		printf("%f, ", average_times_mergesort[i]);
	} printf("\n");
}

void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

void bubbleSort(int arr[], int n) {
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - i - 1; j++) 
			if (arr[j] > arr[j+1])
				swap(&arr[j], &arr[j+1]);
}

int partition(int arr[], int low, int high) {
	int pivot = arr[high];
    int i = (low - 1);
 
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++; 
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
	if (low >= high) return; 
	int pi = partition(arr, low, high);
	quickSort(arr, low, pi - 1);
	quickSort(arr, pi + 1, high);
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    /* create temp arrays */
    int L[n1], R[n2];
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
  
    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
  
    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
  
/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;
  
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
  
        merge(arr, l, m, r);
    }
}
