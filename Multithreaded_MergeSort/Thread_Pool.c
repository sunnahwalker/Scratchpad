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

#ifdef CRITICAL_SECTION
pthread_mutex_t  thread_alloc_mutex  =  PTHREAD_MUTEX_INITIALIZER;
#endif

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

#ifdef CRITICAL_SECTION
#pragma GCC push_options
#pragma GCC optimize ("O0")
#endif
inline int get_thread() {
	static int8_t current_allocation = 0;

	int allocated_thread = 0;
#ifdef CRITICAL_SECTION
	pthread_mutex_lock(&thread_alloc_mutex);
#endif
	//printf("Current Allocation: %u (0x%X), MAX_THREAD: %u\n", current_allocation, current_allocation, MAX_THREADS);
	assert(current_allocation < MAX_THREADS);
	while(local_threads[current_allocation].busy == true) {
		current_allocation = (current_allocation + 1) % MAX_THREADS;
	}

	allocated_thread = current_allocation++;
	current_allocation %= MAX_THREADS;

	//printf("Current Allocation After: %d, MAX_THREAD: %u\n", current_allocation, MAX_THREADS);
	//printf("Allocated: %d\n", allocated_thread);
	assert((local_threads[allocated_thread].busy == false) && (current_allocation < MAX_THREADS));

	local_threads[allocated_thread].busy = true;
#ifdef CRITICAL_SECTION
	pthread_mutex_unlock(&thread_alloc_mutex);
#endif
	THREAD_PRINT("Allocated Thread: %d\n", allocated_thread);
	return (allocated_thread);
}
#ifdef CRITICAL_SECTION
#pragma GCC pop_options
#endif

inline void free_thread(int thread_id) {

	local_threads[thread_id].busy = false;
	THREAD_PRINT("Free Thread: %d\n", thread_id);

	return;
}

