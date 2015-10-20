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

static char CheckLaneNum(int *num)
{
    unsigned char i, j, k;
    char ret = 0;

    if(*num > 250) return ret;

    i = *num / 100;
    j = (*num - i) / 10;
    k = *num - i * 100 - j * 10;

    if(i > 2) return ret;

    if(i > 0)
    {
        j = j * 10 + k;
        if((j >= 10) && (j <= 15))
        {
            ret = 1;
            *num = i * 16 + j;
        }
    }
    else
    {
        if(((j == 1) || (j == 2)) && ((k > 0) && (k < 10)))
        {
            ret = 1;
            *num = j * 16 + k;
        }
    }

    return ret;
}

static void CheckNoneSignalNum(void)
{
    #define MASIZE 5

    unsigned int array[MASIZE] = {0xfffff899, 0xfffffa99, 0xfffffffe, 24, 39999};
    unsigned int i = 0, tmp;

    for(i = 0; i < MASIZE - 1; i++)
    {
        if(array[i+1] < array[i])
        {
            tmp = 0xffffffff - array[i];
            tmp += array[i+1];
        }
        else
        {
            tmp = array[i+1] - array[i];
        }

        array[i] = tmp;
    }

    printf("Time Interval is: ");
    for(i = 0; i < MASIZE - 1; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\r\n");
}

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

    int n = 0;

    printf("pls input num: \r\n");
    scanf("%d", &n);

    printf("check: %d ", CheckLaneNum(&n));
    printf("lane num: %d\r\n", n);

    CheckNoneSignalNum();

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
	while(1);
	
	return 0;
}
