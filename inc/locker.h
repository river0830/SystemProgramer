/* 
 * File: lock.h
 * Author: river
 * Brief: the lock interface head files

 * This program is distributed in hope that it will be useful,
 * but WITHOUT ANY WARRINTY; if some error occurred, pls report it

 * History:
 * 2012-9-27 river created
 */
#ifndef LOCKER_H
#define LOCKER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "typesdef.h"

struct _Locker;
typedef struct _Locker Locker;

typedef Ret (*LockerLock)(Locker *me);
typedef Ret (*LockerTryLock)(Locker *me);
typedef Ret (*LockerUnlock)(Locker *me);
typedef void (*LockerDestroy)(Locker *me);

struct _Locker {
	LockerLock lock;
	LockerTryLock try_lock;
	LockerUnlock unlock;
	LockerDestroy destroy;
	char priv[0];
};

static inline Ret locker_lock(Locker *me)
{
	return_val_if_fail(me != NULL && me->lock != NULL, RET_INVALID_PARAM);

	return me->lock(me);
}

static inline Ret locker_try_lock(Locker *me)
{
	return_val_if_fail(me != NULL && me->try_lock != NULL, RET_INVALID_PARAM);

	return me->try_lock(me);
}

static inline Ret locker_unlock(Locker *me)
{
	return_val_if_fail(me != NULL && me->unlock != NULL, RET_INVALID_PARAM);

	return me->unlock(me);
}	

static inline void locker_destroy(Locker *me)
{
	return_if_fail(me != NULL && me->destroy != NULL);

	me->destroy(me);
	return;
}	


#ifdef __cplusplus
}
#endif

#endif

