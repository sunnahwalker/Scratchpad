//////////////////////////////////////////////////////////////
//
//		Multithreaded Merge Sort App
//		Final project - CMPE 180-94 (Spring 2017)
//		Author: Ahsan Uddin
//		Date: March 6th, 2017
//		Description:
//			1. Create 1000 threads and do unit test on them
//			2. Start merge sort using the threads
//				a. Get new threads and use them for each new sort
//				b. Once 2 sorts are done (wait for thread join), do merge
//
//////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Local includes
#include "BuildCfg.h"
#include "Thread_Pool.h"

#ifdef SORT_PROFILING
const int unsorted_array[SORT_SIZE] = { 27, 14, 19, 26, 10, 31, 33, 44, 42, 35 };
//const int unsorted_array[SORT_SIZE] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
//const int unsorted_array[SORT_SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
#endif

int a[SORT_SIZE] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int b[SORT_SIZE] = {0};
int *sorted_array = &(b[0]);

#ifndef MULTITHREAD
extern void sort(int *arr, int low, int high);
#else
void sort(void * input_params);
#endif


int main() {

	PRINTF("Welcome to Shadow Walker's Multithreaded Merge Sort App!!!\n");
	PRINTF("Code compiled at: %s %s\n", __DATE__, __TIME__);

	Status_t stat = STATUS_ERROR;

#ifdef MULTITHREAD
	thread_param_t main_input;
    PRINTF("Multithreading enabled with %d threads :)\n", MAX_THREADS);
#endif

	stat = thread_unit_test();

	if (stat == STATUS_ERROR) {
		PRINTF("Multithreading unit test failed!!!\n\n");
	}
	else {
		PRINTF("\nThread test passed!!!\n\n");
	}

#ifdef SORT_PROFILING
	clock_t t;
	for (int i = 0; i < MAX_SORT_SAMPLES; i++) {
		PRINTF("\n\nSort Number: %d\n", i+1);
		t = clock();
#endif

		memset(&b[0], 0, (SORT_SIZE * (sizeof(b[0]))));
		memset(&a[0], 0, (SORT_SIZE * (sizeof(a[0]))));
		memcpy((void *)&a[0], (void *)&unsorted_array[0], (SORT_SIZE * (sizeof(unsorted_array[0]))));

		PRINTF("Before Sort:...\n");
		for (int i = 0; i < SORT_SIZE; i++ ) {
			PRINTF("%d\t", a[i]);
		}
		PRINTF("\n\n");

#ifndef MULTITHREAD
		sort(&(a[0]), 0, SORT_SIZE);
#else
		main_input.array = &(a[0]);
		main_input.param1 = 0;
		main_input.param2 = SORT_SIZE;

		sort((void *) &main_input);
#endif

		printf("After Sort:...\n");
		for (int i = 0; i < SORT_SIZE; i++ ) {
			PRINTF("%d\t", sorted_array[i]);
		}

#ifdef SORT_PROFILING
		t = clock() - t;
	}

	PRINTF("\n\nTicks taken for %d sort: %.f", MAX_SORT_SAMPLES, (double)t);

#endif

    PRINTF("\n\nEXIT SUCCESS...\n");

	return 0;
}
