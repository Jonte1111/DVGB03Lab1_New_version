#include "analyze.h"
#include "algorithm.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define BILLION 1E9
#define MAX_SIZE 16384
#define MIN_SIZE 512
#define REPEAT 100 

//
// Private
//
typedef void (*func_pointer_void)(int *a, int n);
typedef bool (*func_pointer_bool)(const int *a, int n, int v);
int* generate_same_number(int* arr, int size) {
	int num = 1;
	for(int i=0;i<size;i++) 
		arr[i] = num;
	return arr;
}
//Generates an array of random numbers
int* generate_random(int* arr, int size){
	srand(time(0));
	for(int i = 0; i < size; i++) {
		arr[i] = rand();	
	}
	return arr;
}
//Generates an array i ascending order
int* generate_sorted(int* arr, int size) {
	for(int i = 0; i < size; i++) {
		arr[i] = i;
	}
	return arr;
}
int* generate_quick_sort(int* arr, int size) {
	for(int i = 0;i< size/2;i++) 
		arr[i] = i;	
	for(int j = size;j>=size/2;j--) 
		arr[j] = j;	
	//for(int k = 0;k<size;k++) 
	//	printf("%d\n", arr[k]);		
	
	return arr;
}
//Generates an array in descending order
int* generate_unsorted(int* arr, int size) {
	int count = 0;
	for(int i = size; i > 0; i--) {
		arr[count] = i;
		count++;
	}
	return arr;
}
int* which_arr(int* arr, int size, const case_t c, const algorithm_t a) {
	/*if(a == binary_search_t || a == linear_search_t) {
		arr = generate_sorted();
	}*/
	//If best case or if a search algo
	if(c == best_t || a > quick_sort_t) {
		arr = generate_sorted(arr, size);
	}
	//If average and sorting algo
	else if(c == average_t) {
		arr = generate_random(arr, size);
	}
	//Special case for quick_sort
	else if(c == worst_t && a == quick_sort_t)
		arr = generate_quick_sort(arr, size);
		//arr = generate_same_number(arr, size);
	//Else unsorted list/worst case
	else
		arr = generate_unsorted(arr, size);
	return arr;
}
void print(int n, double total, const case_t c) {
	if(c == best_t) {
		printf("%d\t%.9fT(s)\t%eT/(N)\t%eT/log(n)\t%eT/nlog(n)\n",
		n, total, total/n, total/log2(n), total/(n*log2(n)));
	}
	else if(c == average_t) {
		printf("%d\t%.9fT(s)\t%eT/(N)\t%eT/nlog(n)\t%eT/(n^2)\n",
		n, total, total/n, total/(n*log2(n)), total/(n*n));
	}
	else {
		printf("%d\t%.9fT(s)\t%eT/nlog(n)\t%eT/n^2\t%eT/n^3\n",
		n, total, total/(n*log2(n)), total/(n*n), total/(n*n*n));
	}
}
//Measures the time of a function
//Measures max amounts of times
//It then returns the average in seconds
int timer_sort(int repeat, func_pointer_void f, int n, const case_t c, const algorithm_t a){
	struct timespec start, stop;
	double total = 0;
	for(int n = 512; n<=16384; n*=2) {
		int* arrP = (int*)malloc(n * sizeof(int));
		arrP = which_arr(arrP, n, c, a);
		for(int i = 0;i<repeat;i++) {
			clock_gettime(CLOCK_MONOTONIC, &start);
			f(arrP, n); 
			clock_gettime(CLOCK_MONOTONIC, &stop);
			total+=(stop.tv_sec*BILLION+stop.tv_nsec)-
			(start.tv_sec*BILLION+start.tv_nsec);
		}
		total = total/BILLION/repeat;
		print(n, total, c);
		free(arrP);
	}
	return total;
}
int timer_search(const case_t c, const algorithm_t a, int repeat, func_pointer_bool f){
	int m = MAX_SIZE;
	int n = MIN_SIZE;
	struct timespec start, stop;
	double total = 0;
	int v;
	while(n <= m ) {
		int* arrP = (int*)malloc(n * sizeof(int));
		arrP = generate_sorted(arrP, n);
		//Scuffed fixa det här
		if((c == best_t && a == linear_search_t) || (c == worst_t && a == binary_search_t))
			v = arrP[0];
		else if(c == worst_t && a == linear_search_t)
			v = -1;
		else if(c == best_t && a == binary_search_t)
			v = arrP[n/2];
		else 
			v = arrP[rand() % (n-1 + 1 - 0)]; 
				
		for(int i = 0;i<repeat;i++) {
			clock_gettime(CLOCK_MONOTONIC, &start);
			f(arrP, n, v); 
			clock_gettime(CLOCK_MONOTONIC, &stop);
			total+=(stop.tv_sec*BILLION+stop.tv_nsec)-
			(start.tv_sec*BILLION+start.tv_nsec);
		}
		free(arrP);
		total = total/BILLION/repeat;
		print(n, total, c);
		n*=2;
	}
	return total;
}
//Generate an array based on the worst case for a given algorithm
void worst_case(const algorithm_t a, int n, const case_t c){ 
	//Create a pointer to a function
	//and an array
	int r = REPEAT;
	//int size = MAX_SIZE;
	func_pointer_void fvp;
	//func_pointer_bool fbp;
	if(a == bubble_sort_t) {
		fvp = bubble_sort;
		//if algorithm_t > quick_sort_t = search
		//Worst case for bubblesort is a reversed array
		printf("Bubble sort worst case:\n");
		timer_sort(r, fvp, n, c, a);
	}
	else if(a == insertion_sort_t) {
		fvp = insertion_sort;
		printf("Insertion sort worst case:\n");
		timer_sort(r, fvp, n, c, a);
	}
	else if(a == quick_sort_t) {
		fvp = quick_sort;
		timer_sort(r, fvp, n, c, a);
		printf("Quick sort worst case:\n");
	}
	else if(a == linear_search_t) {
		//fbp = linear_search;
		printf("Linear search worst case:\n");
		//fbp(arrP, 1, 2);
	}
	else {
		//fbp = binary_search;
		printf("Binary search worst case:\n");
		//fbp(arrP, 1, 2);
	}
	
}
void average_case(const algorithm_t a, int n, const case_t c) {
	int r = REPEAT;
	//int size = MAX_SIZE;
	func_pointer_void fvp;
       	if(a == bubble_sort_t)	{
		fvp = bubble_sort;
		//Worst case for bubblesort is a reversed array
		printf("Bubble Sort average case\n");
		timer_sort(r, fvp, n, c, a);
	}
	else if(a == insertion_sort_t) {
		fvp = insertion_sort;
		//Worst case for bubblesort is a reversed array
		printf("Insertion Sort average case\n");
		timer_sort(r, fvp, n, c, a);
	}
	else if(a == quick_sort_t) {
		fvp = quick_sort;
		timer_sort(r, fvp, n, c, a);
		printf("Quick Sort average case\n");
	}
	else if(a == linear_search_t) {
		printf("Linear Search average case\n");
	}
	else {
		printf("Binary Search average case\n");
		}
}
void best_case(const algorithm_t a, int n, const case_t c) {
	int r = REPEAT;
	//int size = MAX_SIZE;
	func_pointer_void fvp;
	if(a == bubble_sort_t)	{
		fvp = bubble_sort;
		printf("Bubble Sort best case\n");
		timer_sort(r, fvp, n, c, a);
	}
	else if(a == insertion_sort_t) {
		fvp = insertion_sort;
		printf("Insertion Sort best case\n");
		timer_sort(r, fvp, n, c, a);
	}
	else if(a == quick_sort_t) {
		fvp = quick_sort;
		timer_sort(r, fvp, n, c, a);
		printf("Quick Sort best case\n");
	}
	else if(a == linear_search_t) {
		printf("Linear Search best case\n");
	}
	else {
		printf("Binary Search best case\n");
	}
}
void search_case(const case_t c, const algorithm_t a, int n) {
	int r = REPEAT;
	//int size = MAX_SIZE;
	func_pointer_bool fbp;
	//int* arrP = (int*)malloc(size * sizeof(int));
	if(a == linear_search_t)
		fbp = linear_search;
	else
		fbp = binary_search;
	//In all cases the array is sorted
	printf("search");
	timer_search(c, a, r, fbp);
}
//Determines if case is worst, average or best
void determine_case(const case_t c, const algorithm_t a, int n) {
	if(a > quick_sort_t)
		search_case(c, a, n);
	else if(c == worst_t) 
		worst_case(a, n, c);
	else if(c == average_t)
		average_case(a, n, c);
	else
		best_case(a, n, c);
}
//
// Public
//
void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n)
{
	determine_case(c, a, n);
}
