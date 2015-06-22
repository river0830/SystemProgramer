#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "rw_locker.h"

typedef enum {
	RW_LOCK_NONE = 0,
	RW_LOCK_WR,
	RW_LOCK_RD
}LockMode;

struct _RWLock {
	int read_nest;
	LockMode mode;
	Locker *wrlock;
	Locker *rdlock;		//protect read_nest change
};

Ret rwlock_wrlock(RWLock *me) 
{
	Ret ret = RET_OK;
	
	return_val_if_fail(me != NULL && me->wrlock != NULL, RET_INVALID_PARAM);

	ret = locker_lock(me->wrlock);
	if(ret == RET_OK) {
		me->mode = RW_LOCK_WR;
	}

	return ret;
}

Ret rwlock_rdlock(RWLock *me)
{
    Ret ret = RET_OK;

	return_val_if_fail(me != NULL && me->rdlock != NULL, RET_INVALID_PARAM);

	ret = locker_lock(me->rdlock);		//protect read_nest
	if(ret == RET_OK) {
		me->read_nest += 1;
		if(me->read_nest == 1) {
			me->mode = RW_LOCK_RD;
			ret = locker_lock(me->wrlock);
		}
		locker_unlock(me->rdlock);
	}

	return ret;
}
	
Ret rwlock_unlock(RWLock *me)
{
	Ret ret = RET_OK;

	return_val_if_fail(me != NULL, RET_INVALID_PARAM);

	if(me->mode == RW_LOCK_WR) {
		me->mode = RW_LOCK_NONE;
		ret = locker_unlock(me->wrlock);
	} else {
		assert(me->mode == RW_LOCK_RD);
		ret = locker_lock(me->rdlock);
		if(ret == RET_OK) {
			me->read_nest -= 1;
			if(me->read_nest == 0) {
				me->mode = RW_LOCK_NONE;
				ret = locker_unlock(me->wrlock);
			}
			locker_unlock(me->rdlock);
		}
	}

	return ret;
}

void rwlock_destroy(RWLock *me)
{
	return_val_if_fail(me != NULL, RET_INVALID_PARAM);

	locker_destroy(me->rdlock);
	locker_destroy(me->wrlock);
	free(me);
	me = NULL;
}

RWLock *rwlock_create(Locker *wrlock, Locker *rdlock)
{
	RWLock *me = NULL;

	me = (RWLock *)malloc(sizeof(RWLock));
	if(me != NULL) {
		me->mode = RW_LOCK_NONE;
		me->read_nest = 0;
		me->wrlock = wrlock;
		me->rdlock = rdlock;
	}

	return me;
}
