/* 
 * File: locker_pthread_nest.h
 * Author: river
 * Brief: the linux pthread nest lock head files, decorate mode

 * This program is distributed in hope that it will be useful,
 * but WITHOUT ANY WARRINTY; if some error occurred, pls report it

 * History:
 * 2012-9-28 river created
 */
#ifndef LOCKER_PTHREAD_NEST_H
#define LOCKER_PTHREAD_NEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "locker.h"

typedef int (*ReadSelfId)(void);

Locker *locker_pthread_nest_create(Locker *lock, ReadSelfId taskself);



#ifdef __cplusplus
}
#endif

#endif

