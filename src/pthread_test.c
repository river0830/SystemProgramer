#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include "dlist.h"
#include "test.h"
#include "locker_pthread.h"
#include "locker_pthread_nest.h"

static void *producer_thread(void *arg)
{
	int i = 0;
	DList *dlist = (DList *)arg;
	
	printf("producer thread executed\n");
	printf("append data\n");
	
	for(i = 0; i < 1000; i++) 
		dlist_insert(dlist, 0, (void *)i);

	sleep(1);
	printf("prepend data to dlist \n");
	
	for(i = 0; i < 1000; i++) 
		dlist_prepend(dlist, (void *)i);
	
	return NULL;
}

static void *consumer_thread(void *arg)
{
	int i = 0;
	DList *dlist = (DList *)arg;
	
	printf("consumer thread executed!\n");
	for(i = 0; i < 2000; i++) {
		usleep(20);
		printf("dlist length = %d\n", dlist_length(dlist));
		dlist_find(dlist, cmp_int, (void *)i);
	}
	
	return NULL;
}


void test_pthread(void)
{
	pthread_t consumer_t = 0;
	pthread_t producer_t = 0;
	Locker *wrlock = locker_pthread_create();
	Locker *nest_lock = locker_pthread_nest_create(wrlock, (ReadSelfId)pthread_self);
#ifdef RW_LOCK
	Locker *rdlock = locker_pthread_create();
	RWLock *rwlock = rwlock_create(wrlock, rdlock);
#endif
	DList *head = NULL;
	
#ifdef RW_LOCK
	head = dlist_create(rwlock);
#else
	head = dlist_create(wrlock);
#endif
	return_if_fail(head != NULL);
	
	pthread_create(&producer_t, NULL, producer_thread, head);
	pthread_create(&consumer_t, NULL, consumer_thread, head);

	pthread_join(consumer_t, NULL);
	pthread_join(producer_t, NULL);
}



