/*
 * File:   philosopher.c
 * Author: river
 * Brief:  a simple test, the linux thread dead lock
 *
 * This program is distributed in hope that it will be useful,
 * but WITHOUT ANY WARRANTY.

 * History:
 * 2012-10-10 river created
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "typesdef.h"
#include "locker.h"
#include "locker_pthread.h"

#define PHILO_NUM 5
#define TICKS 	100

typedef struct  
{
	int id;
	char str[PHILO_NUM];
	int left_chopstick;
	int right_chopstick;
}PhilosopherInfo;

static Locker *chopsticks[PHILO_NUM];

static PhilosopherInfo philo_info_table[PHILO_NUM] = {
	{0, "A", 4, 0},
	{1, "B", 0, 1},
	{2, "C", 1, 2},
	{3, "D", 2, 3},
	{4, "E", 3, 4}
};

static void *philosopher_thread(void *arg)
{
	PhilosopherInfo *priv = (PhilosopherInfo *)arg;
	Ret ret;
	static int flag1[PHILO_NUM] = {0};
	static int flag2[PHILO_NUM] = {0};

	while(1) {	
		usleep((priv->id+1)*TICKS);				//thinking
		
		if(!flag1[priv->id]) {
			ret = locker_try_lock(chopsticks[priv->left_chopstick]);
			if(ret == RET_OK) {
				flag1[priv->id] = 1;
				printf("philosopher %s fetches chopsticks %d\n", priv->str, priv->left_chopstick+1);
			} else {
				printf("philosopher %s don't fetchest chopsticks %d\n", priv->str, priv->left_chopstick+1);
			}
		} 

		if(!flag2[priv->id]) {
			ret = locker_try_lock(chopsticks[priv->right_chopstick]);
			if(ret == RET_OK) {
				flag2[priv->id] = 1;
				printf("philosopher %s fetches chopsticks %d\n", priv->str, priv->right_chopstick+1);
			} else {
				printf("philosopher %s don't fetches chopsticks %d\n", priv->str, priv->right_chopstick+1);
			}
		}
#if 1
		if(flag1[priv->id]) {
			if(!flag2[priv->id]) {
				flag1[priv->id] = 0;
				locker_unlock(chopsticks[priv->left_chopstick]);
				printf("philosopher %s release already fetched chopsticks %d\n", priv->str, priv->left_chopstick+1);
			}
		}

		if(flag2[priv->id]) {
			if(!flag1[priv->id]) {
				flag2[priv->id] = 0;
				locker_unlock(chopsticks[priv->right_chopstick]);
				printf("philosopher %s release already fetched chopsticks %d\n", priv->str, priv->right_chopstick+1);
			}
		}
#endif		

		if(flag1[priv->id] && flag2[priv->id]) {
			printf("philosopher %s start eating\n", priv->str);
			usleep(TICKS);			//eating
			printf("philosopher %s release chopsticks %d %d\n", priv->str, priv->left_chopstick+1, priv->right_chopstick+1);
			flag1[priv->id] = 0;
			flag2[priv->id] = 0;
			locker_unlock(chopsticks[priv->left_chopstick]);
			locker_unlock(chopsticks[priv->right_chopstick]);
		}
	}
}
	

void philosopher_problem(void)
{
	pthread_t philo_t[PHILO_NUM] = {0};
	int i = 0;

	for(i = 0; i < PHILO_NUM; i++) 
		chopsticks [i] = locker_pthread_create();

	for(i = 0; i < PHILO_NUM; i++)
		pthread_create(&philo_t[i], NULL, philosopher_thread, &philo_info_table[i]);
	
	for(i = 0; i < PHILO_NUM; i++)
		pthread_join(philo_t[i], NULL);

	for(i = 0; i < PHILO_NUM; i++)
		locker_destroy(chopsticks[i]);

	return;
}

	
