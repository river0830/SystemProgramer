/*
 * File: rw_locker.h
 * Author: river
 * Brief: the interface of rwlock

 * This program is distributed in hope that it will be useful,
 * but WITHOUT ANY WARRANTY.

 * History:
 * 2012-9-29 created
 */
#ifndef RW_LOCKER_H
#define RW_LOCKER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "locker.h"

struct _RWLock;
typedef struct _RWLock RWLock;

RWLock *rwlock_create(Locker *wrlock, Locker*rdlock);
Ret rwlock_rdlock(RWLock *me);
Ret rwlock_wrlock(RWLock *me);
Ret rwlock_unlock(RWLock *me);
void rwlock_destroy(RWLock *me);

#ifdef __cplusplus
}
#endif

#endif
