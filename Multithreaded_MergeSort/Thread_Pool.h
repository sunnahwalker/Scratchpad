/*
 * Thread_Pool.h
 *
 *  Created on: Mar 9, 2017
 *      Author: root
 */

#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <assert.h>
#include <err.h>

//#include "Thread_Pool.h"
#include "BuildCfg.h"

#ifdef GREEDY
#define MAX_THREADS (SORT_SIZE*10)
#else
#define MAX_THREADS (SORT_SIZE*2)
#endif

typedef struct{
	pthread_t thread;
	bool busy;
}thread_t;

#ifdef MULTITHREAD
typedef struct{
	int *array;
	int param1;
	int param2;
	int param3;
	//int thread_id;
} thread_param_t;
#endif

void thread_init();
Status_t thread_unit_test();
void *test_func(void *threadid);

int get_thread();
void free_thread(int thread_id);

#endif /* THREAD_POOL_H_ */
