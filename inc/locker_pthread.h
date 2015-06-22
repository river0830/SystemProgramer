/* 
 * File: lock.h
 * Author: river
 * Brief: the linux pthread lock head files

 * This program is distributed in hope that it will be useful,
 * but WITHOUT ANY WARRINTY; if some error occurred, pls report it

 * History:
 * 2012-9-27 river created
 */
#ifndef LOCKER_PTHREAD_H
#define LOCKER_PTHREAD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "locker.h"

Locker *locker_pthread_create(void);


#ifdef __cplusplus
}
#endif

#endif

