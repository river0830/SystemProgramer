#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "locker.h"
#include "locker_pthread_nest.h"

typedef struct 
{
	int owner;			//the task id
	int nest;			//nest times
	ReadSelfId read_id;
	Locker *lock;
} NestPrivInfo;

static Ret locker_pthread_nest_lock(Locker *me)
{
    NestPrivInfo *priv = (NestPrivInfo *)me->priv;
	Ret ret = RET_OK;
	
	if(priv->owner == priv->read_id()) {		//the task is already locked
		priv->nest++;
	} else {					
		ret = locker_lock(priv->lock);

		if(ret == RET_OK) {
			priv->nest = 1;
			priv->owner = priv->read_id();
		}
	}

	return ret;
}

static Ret locker_pthread_nest_try_lock(Locker *me)
{
    NestPrivInfo *priv = (NestPrivInfo *)me->priv;
	Ret ret = RET_OK;
	
	if(priv->owner == priv->read_id()) {		//the task is already locked
		priv->nest++;
	} else {					
		ret = locker_try_lock(priv->lock);

		if(ret == RET_OK) {
			priv->nest = 1;
			priv->owner = priv->read_id();
		}
	}

	return ret;
}


static Ret locker_pthread_nest_unlock(Locker *me)
{
    NestPrivInfo *priv = (NestPrivInfo *)me->priv;
	int ret = RET_OK;

	if(priv->owner != priv->read_id()) {
		ret = RET_FAIL;
	} else {
		priv->nest--;
		if(priv->nest == 0) {
			priv->owner = 0;
			ret = locker_unlock(priv->lock);
		}
	}

	return ret;
}

static void locker_pthread_nest_destroy(Locker *me)
{
    NestPrivInfo *priv = (NestPrivInfo *)me->priv;

	priv->owner = 0;
	priv->nest = 0;
	locker_destroy(priv->lock);
	priv->lock = NULL;
    free(me);
    me = NULL;

	return;
}


Locker *locker_pthread_nest_create(Locker *lock, ReadSelfId taskself)
{
    Locker *me = NULL;

	return_val_if_fail(lock != NULL && taskself != NULL, NULL);

    me = (Locker *)malloc(sizeof(Locker) + sizeof(NestPrivInfo));
    if(me != NULL) {
        NestPrivInfo *priv = (NestPrivInfo *)me->priv;

        me->lock = locker_pthread_nest_lock;
        me->try_lock = locker_pthread_nest_try_lock;
        me->unlock = locker_pthread_nest_unlock;
        me->destroy = locker_pthread_nest_destroy;

		priv->read_id = taskself;
		priv->lock = lock;
		priv->owner = 0;
		priv->nest = 0;
	}

    return me;
}

