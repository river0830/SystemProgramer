#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _LINUX_P
#ifdef _LINUX_P
#include <unistd.h>
#include <pthread.h>
#endif

#include "test.h"
#include "PolynomialFitting.h"

extern void philosopher_problem(void);

static void *pthread_test(void *arg)
{
	char *str = (char *)arg;

	printf("the first child thread\n");
	printf("%s %s\r\n", __func__, str);
	test();
	test_container();
#if 0
    test_pthread();
	philosopher_problem();
#endif

    testfit();

	return NULL;
}

int main(void)
{
	pthread_t tid;
	void *ret = NULL;
	int err;

	err = pthread_create(&tid, NULL, pthread_test, "executed");
	if(err != 0) {
		printf("can't create pthread: %s\n", strerror(err));
		exit(1);
	}
	printf("main thread\n");

    pthread_join(tid, &ret);
	
	return 0;
}
