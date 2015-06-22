#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "locker.h"
#include "locker_pthread.h"

typedef struct 
{
	pthread_mutex_t mutex;
} PthreadMutexPriv;

static Ret locker_pthread_lock(Locker *me)
{
	PthreadMutexPriv *priv = (PthreadMutexPriv *)me->priv;
	int ret = pthread_mutex_lock(&priv->mutex);

	return ret == 0 ? RET_OK : RET_FAIL;
}

static Ret locker_pthread_try_lock(Locker *me)
{
	PthreadMutexPriv *priv = (PthreadMutexPriv *)me->priv;
	int ret = pthread_mutex_trylock(&priv->mutex);

	return ret == 0 ? RET_OK : RET_FAIL;
}

static Ret locker_pthread_unlock(Locker *me)
{
	PthreadMutexPriv *priv = (PthreadMutexPriv *)me->priv;
	int ret = pthread_mutex_unlock(&priv->mutex);

	return ret == 0 ? RET_OK : RET_FAIL;
}

static void locker_pthread_destroy(Locker *me)
{
	PthreadMutexPriv *priv = (PthreadMutexPriv *)me->priv;

	pthread_mutex_destroy(&priv->mutex);
	free(me);
	me = NULL;

	return;
}


Locker *locker_pthread_create(void)
{
	Locker *me = NULL;

	me = (Locker *)malloc(sizeof(Locker) + sizeof(PthreadMutexPriv));
	if(me != NULL) {
		PthreadMutexPriv *priv = (PthreadMutexPriv *)me->priv;

		me->lock = locker_pthread_lock;
		me->try_lock = locker_pthread_try_lock;
		me->unlock = locker_pthread_unlock;
		me->destroy = locker_pthread_destroy;
		pthread_mutex_init(&(priv->mutex), NULL);
	}

	return me;
}
				
		
