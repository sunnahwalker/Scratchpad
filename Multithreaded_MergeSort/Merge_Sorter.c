//////////////////////////////////////////////////////////////
//
//		Multithreaded Merge Sort App
//		Final project - CMPE 180-94 (Spring 2017)
//		Author: Ahsan Uddin
//		Date: March 9th, 2017
//		Description:
//
//
//////////////////////////////////////////////////////////////


#include "BuildCfg.h"
#include "Thread_Pool.h"
#include <errno.h>

extern int *sorted_array;
#ifdef MULTITHREAD
extern thread_t local_threads[];
#endif

void merging(int *arr, int low, int mid, int high) {
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

   return;
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

   int thread_1, thread_2;
   int stat = 1;
	int low = 0;
	int mid = 0;
	int high = 0;
   thread_param_t sort_param1, sort_param2;
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
			err(stat, "Thread Join FATAL error: ");
			assert(false);
		}
		stat = pthread_join(local_threads[thread_2].thread,NULL);
		if (stat) {
			err(stat, "Thread Join FATAL error: ");
			assert(false);
		}

		free_thread(thread_1);
		free_thread(thread_2);

		merging(input_sort_param->array, low, mid, high);

		//pthread_exit(EXIT_SUCCESS);
		return NULL;
   }
   else {
	  //pthread_exit(EXIT_SUCCESS);
      return NULL;
   }

}
#endif	//MULTITHREAD
