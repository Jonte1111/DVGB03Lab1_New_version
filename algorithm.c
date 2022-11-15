#include "algorithm.h"
#include <stdio.h>

//
// Private
//
void swap(int* xp, int* yp) {
	int tmp = *xp;
	*xp = *yp;
	*yp = tmp;
}

int partition(int* a, int low, int high, int n){
	//int pivot = n;
	//int i = low - 1;
	//int j = high + 1;

	/*while(true) {
		do{
			i++;
		}while(a[i] < pivot);

		do{
			j--;
		}while(a[j] > pivot);

		if(i >= j)
			return j;
		swap(&a[i], &a[j]);
	}*/
	int pivot = a[high];
	int i = (low - 1);
	for(int j = low; j <= high - 1; j++) {
		if(a[j] < pivot) {
			i++;
			swap(&a[i], &a[j]);
		}
	}
	swap(&a[i + 1], &a[high]);
	return (i + 1);
}
void recursion(int* a, int low, int high, int n) {
	if(low<high) {
		int q = partition(a, low, high, n);
		recursion(a, low, q - 1, n);
		recursion(a, q + 1, high, n);
	}
}
//		REMOVE THIS LATER
//Test function to see if array is sorted correctly
void test_sorted(int*a , int size) {
	for(int i = 0;i<size;i++) {
		printf("%d\n",a[i]);
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
				//printf("%d%d\n", a[j], a[j+1]); 
				swap_i = true;
			}
		}
		if(!swap_i)
			break;
	}
	//test_sorted(a, n);
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
	//test_sorted(a, n);
}	

void quick_sort(int *a, int n)
{
	int low = 0;
	int high = n-1;
	int count = 0;
	for(int i = 0;i < n;i++) {
		count += i;
	}
	count = count/n;
	recursion(a, low, high, count);
	//test_sorted(a, n);
	
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
