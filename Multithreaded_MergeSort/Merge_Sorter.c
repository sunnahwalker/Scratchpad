//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		Multithreaded Merge Sort App
//		Final project - CMPE 180-94 (Spring 2017)
//		Author: Ahsan Uddin
//		Date: March 9th, 2017
//		Description:
//			1. Create 1000 threads and do unit test on them
//			2. Start merge sort using the threads
//				a. Get new threads and use them for each new sort
//				b. Once 2 sorts are done (wait for thread join), do merge
//
//
//		Note: The merge sort code itself is copied from Tutorialspoint
//		(https://www.tutorialspoint.com/data_structures_algorithms/merge_sort_program_in_c.htm)
//		The intent of this code is to demo the multithreaded
//		behavior and not the merge sort code itself
//
//////////////////////////////////////////////////////////////////////////////////////////////////////


#include "BuildCfg.h"
#include "Thread_Pool.h"
#include <errno.h>

extern int *sorted_array;
#ifdef MULTITHREAD
extern thread_t local_threads[];
#endif

#ifndef MULTITHREAD_MERGE
void merging(int *arr, int low, int mid, int high) {
#else
void *merging(void * input_params) {
	int *arr, low, mid, high;

	thread_param_t *input_merge_param = (thread_param_t *) input_params;

	arr  = input_merge_param->array;
	low  = input_merge_param->param1;
	mid  = input_merge_param->param2;
	high = input_merge_param->param3;
#endif

   int l1, l2, i;

   for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
      if(arr[l1] <= arr[l2])
    	 sorted_array[i] = arr[l1++];
      else
    	 sorted_array[i] = arr[l2++];
   }

   while(l1 <= mid)
	  sorted_array[i++] = arr[l1++];

   while(l2 <= high)
	  sorted_array[i++] = arr[l2++];

   for(i = low; i <= high; i++)
      arr[i] = sorted_array[i];

#ifndef MULTITHREAD_MERGE
   return;
#else
   return NULL;
#endif
}


#ifndef MULTITHREAD								// Do single threaded as normal
void sort(int *arr, int low, int high) {
	int mid;
   if(low < high) {
      mid = (low + high) / 2;
      sort(arr, low, mid);
      sort(arr, mid+1, high);
      merging(arr, low, mid, high);
   }
   else {
      return;
   }
}

#else	//MULTITHREAD							// Lets burn some threads, shall we?
void* sort(void * input_params) {

	int thread_1, thread_2, thread_3;
	int stat = 1;
	int low = 0;
	int mid = 0;
	int high = 0;
	thread_param_t sort_param1, sort_param2, merge_param;
	thread_param_t *input_sort_param = (thread_param_t *) input_params;

	low = input_sort_param->param1;

	high = input_sort_param->param2;

	if(low < high) {
		mid = (low + high) / 2;

		sort_param1.array  = input_sort_param->array;
		sort_param1.param1 = low;
		sort_param1.param2 = mid;

		//Allocate the first thread
		thread_1 = get_thread();
		stat = pthread_create(&(local_threads[thread_1].thread),NULL,sort,(void*) &sort_param1);

		// Proceed if thread creation was ok
		assert(stat == EXIT_SUCCESS);

		sort_param2.array  = input_sort_param->array;
		sort_param2.param1 = mid + 1;
		sort_param2.param2 = high;

		//Allocate the second thread
		thread_2 = get_thread();
		stat = pthread_create(&(local_threads[thread_2].thread),NULL,sort,(void*) &sort_param2);

		// Proceed if thread creation was ok
		assert(stat == EXIT_SUCCESS);

		stat = pthread_join(local_threads[thread_1].thread,NULL);
		if (stat) {
			err(stat, "Sort Thread Join FATAL error: ");
			assert(false);
		}
		stat = pthread_join(local_threads[thread_2].thread,NULL);
		if (stat) {
			err(stat, "Sort Thread Join FATAL error: ");
			assert(false);
		}

		free_thread(thread_1);
		free_thread(thread_2);


#ifdef MULTITHREAD_MERGE
		merge_param.array = input_sort_param->array;
		merge_param.param1 = low;
		merge_param.param2 = mid;
		merge_param.param3 = high;

		//Allocate the third thread
		thread_3 = get_thread();
		stat = pthread_create(&(local_threads[thread_3].thread),NULL,merging,(void*) &merge_param);

		// Proceed if thread creation was ok
		assert(stat == EXIT_SUCCESS);

		stat = pthread_join(local_threads[thread_3].thread,NULL);
		if (stat) {
			err(stat, "Merge Thread Join FATAL error: ");
			assert(false);
		}

		free_thread(thread_3);
#else
		merging(input_sort_param->array, low, mid, high);
#endif
	}

	return NULL;
}
#endif	//MULTITHREAD
