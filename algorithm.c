#include "algorithm.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//
// Private
//
void swap(int* xp, int* yp) {
	int tmp = *xp;
	*xp = *yp;
	*yp = tmp;
}

int partition(int* a, int low, int high){
	int pivot = a[low];
	int i = low - 1;
	int j = high + 1;

	while(1) {
		do {
			i++;
		}while(a[i] < pivot);
		do{
			j--;
		}while(a[j] > pivot);
		if(i >= j)
			return j;

		swap(&a[i], &a[j]);
	}

}
int partition_r(int* a, int low, int high) {
	srand(time(0));
	int random = low + rand() % (high - low);
	swap(&a[random], &a[low]);

	return partition(a, low, high);
}
void recursion(int* a, int low, int high) {
	if(low<high) {
		int q = partition_r(a, low, high);
			recursion(a, low, q);
			recursion(a, q + 1, high);
	}
}
//
// Public
//
void bubble_sort(int *a, int n)
{
	int i, j;
	bool swap_i;
	for(i = 0; i < n - 1; i++) {
		swap_i = false;
		for(j = 0; j < n - i - 1; j++) {
			if(a[j] > a[j+1]) {
				swap(&a[j], &a[j+1]);
				swap_i = true;
			}
		}
		if(!swap_i)
			break;
	}
}
void insertion_sort(int *a, int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;

        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = key;
    }
}	

void quick_sort(int *a, int n)
{
	int low = 0;
	int high = n-1;
	recursion(a, low, high);
	for(int i = 0;i < n;i++)
		printf("%d\n", a[i]);
}

bool linear_search(const int *a, int n, int v)
{
	//Loop through the array
	//if element found return true
	//else return false
	for(int i = 0; i < n; i++) {
		if(a[i] == v)
			return true;
	}
	return false;
}

bool binary_search(const int *a, int n, int v)
{
	//low = first element, high = last element
	//smallest and biggest element since list is sorted
	int low = a[0];
	int high = a[n];
	int mid;
	while(low != high) {
		mid = (low + high) / 2;	
		if(v == a[mid])
			return true;
		else if(v > a[mid])
			low = mid+1;
		else
			high = mid - 1;
	}
	return false;
}
