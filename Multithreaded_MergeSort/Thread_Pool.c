///////////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////////

// Local includes (contains Global includes too!)
#include "Thread_Pool.h"

pthread_mutex_t  thread_alloc_mutex  =  PTHREAD_MUTEX_INITIALIZER;
thread_t local_threads[MAX_THREADS];

void thread_init()
{
	for (int i = 0; i < MAX_THREADS; i++) {
		local_threads[i].busy = false;
	}
	return;
}

Status_t thread_unit_test()
{
	Status_t stat = STATUS_OK;
	int rc = 0;

	for(int i=0; i < MAX_THREADS; i++){
		UNIT_TEST_PRINTF("%s: Creating thread %d\n", __func__, i);
	    assert(local_threads[i].busy == false);
		rc = pthread_create(&(local_threads[i].thread), NULL, test_func, (void *)i);
	    if (rc){
	    	UNIT_TEST_PRINTF("ERROR; return code from pthread_create() is %d\n", rc);
	        exit(-1);
	    }
	    local_threads[i].busy = true;
	}

	UNIT_TEST_PRINTF("Joining all threads now!!!\n");
	for(int i=0; i < MAX_THREADS; i++){
	  	pthread_join(local_threads[i].thread, NULL);
	  	local_threads[i].busy = false;
	}
	UNIT_TEST_PRINTF("All threads joined :)\n\n");

	UNIT_TEST_PRINTF("Recreating all threads now!!!\n");
	for(int i=0; i < MAX_THREADS; i++){
		UNIT_TEST_PRINTF("%s: Creating thread %d\n", __func__, i);
		assert(local_threads[i].busy == false);
		rc = pthread_create(&(local_threads[i].thread), NULL, test_func, (void *)i);
		if (rc){
			UNIT_TEST_PRINTF("ERROR; return code from pthread_create() is %d\n", rc);
		    exit(-1);
		}
		local_threads[i].busy = true;
	}

	UNIT_TEST_PRINTF("\n\nJoining all threads now!!!\n");
	for(int i=0; i < MAX_THREADS; i++){
	 	pthread_join(local_threads[i].thread, NULL);
	 	local_threads[i].busy = false;
	}
	UNIT_TEST_PRINTF("All threads joined again before final release!:)\n\n");

	return stat;
}

void *test_func(void *threadid)
{
   int tid;
   tid = (int)threadid;
   UNIT_TEST_PRINTF("Hello World! It's me, thread #%d!\n", tid);
   pthread_exit(NULL);
}

int get_thread() {
	static int current_allocation = 0;

	int allocated_thread = 0;

	pthread_mutex_lock(&thread_alloc_mutex);
	allocated_thread = current_allocation++;
	assert((current_allocation < (MAX_THREADS - 1)) && (local_threads[current_allocation].busy == false));
	local_threads[allocated_thread].busy = true;
	pthread_mutex_unlock(&thread_alloc_mutex);

	THREAD_PRINT("Allocated Thread: %d\n", allocated_thread);
	return (allocated_thread);
}

void free_thread(int thread_id) {

	local_threads[thread_id].busy = false;
	THREAD_PRINT("Free Thread: %d\n", thread_id);

	return;
}

