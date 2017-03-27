/*
 * BuildCfg.h
 *
 *  Created on: Mar 9, 2017
 *      Author: Ahsan Uddin
 */

#ifndef BUILDCFG_H_
#define BUILDCFG_H_

typedef enum {
	STATUS_OK,
	STATUS_ERROR
}Status_t;

#define SORT_SIZE 10

#define noUNIT_TEST_PRINTS

#define MULTITHREAD

#ifdef MULTITHREAD
#define	noGREEDY					// If there are huge pool of threads!
#define CRITICAL_SECTION			// Flag for Mutex
#define MULTITHREAD_MERGE			// Flag for seperate thread for Merging
#endif

#ifdef MULTITHREAD
#define THREAD_PRINT(str,s...) //PRINTF(str,##s)
#else
#define THREAD_PRINT(str,s...)
#endif


#ifdef UNIT_TEST_PRINTS
#define UNIT_TEST_PRINTF(str,s...) PRINTF(str,##s)
#else
#define UNIT_TEST_PRINTF(str,s...)
#endif

#define PRINTF(str,s...) printf(str,##s)

#endif /* BUILDCFG_H_ */
