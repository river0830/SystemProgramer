#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "dlist.h"

struct _DList
{
	struct _DList *prev;
	struct _DList *next;
#ifndef RW_LOCK
	Locker *lock;
#else
	RWLock *lock;
#endif
	void *data;
};

static void _dlist_add(DList *new_list, DList *prev, DList *next)
{
	prev->next = new_list;
	next->prev = new_list;
	new_list->prev = prev;
	new_list->next = next;
}

static DList *get_dlist_item(DList *head, int index, int fail_return_last)
{
	DList *tmp = head->next;
	int i = 0;

	if(index == -1)
		tmp = head;
		
	while(tmp != head) {
		if(i == index)
			break;
		tmp = tmp->next;
		i++;
	}

	if(!fail_return_last) {
		if(tmp == head)
			tmp = NULL;
	}
	
	return tmp;
}

#ifndef RW_LOCK
static void dlist_lock(DList *this)
{
	if(this->lock != NULL) {
		locker_lock(this->lock);
	}
}

static void dlist_unlock(DList *this)
{
	if(this->lock != NULL) {
		locker_unlock(this->lock);
	}
}

static void dlist_destroy_lock(DList *this)
{
	if(this->lock != NULL) {
		locker_unlock(this->lock);
		locker_destroy(this->lock);
	}
}
#else
static void dlist_rdlock(DList *this)
{
	if(this->lock != NULL) {
		rwlock_rdlock(this->lock);
	}
}

static void dlist_wrlock(DList *this)
{
	if(this->lock != NULL) {
		rwlock_wrlock(this->lock);
	}
}


static void dlist_unlock(DList *this)
{
	if(this->lock != NULL) {
		rwlock_unlock(this->lock);
	}
}

static void dlist_destroy_lock(DList *this)
{
	if(this->lock != NULL) {
		rwlock_unlock(this->lock);
		rwlock_destroy(this->lock);
	}
}
#endif

#ifndef RW_LOCK
DList *dlist_create(Locker *lock)
#else
DList *dlist_create(RWLock *lock)
#endif
{
	DList *head = NULL;

	head = (DList *)malloc(sizeof(DList));
	return_val_if_fail(head != NULL, NULL);
	memset(head, 0, sizeof(DList));

	head->prev = head->next = head;
	head->lock = lock;
	return head;
}

void dlist_destroy(DList *head)
{
	DList *tmp = NULL, *tmp1 = NULL;

	return_if_fail(head != NULL);
#ifdef RW_LOCK
	dlist_wrlock(head);
#else
	dlist_lock(head);
#endif

	tmp = head->next;
	while(tmp != head) {
		tmp1 = tmp;
		free(tmp);
		tmp = tmp1->next;
	}

	dlist_destroy_lock(head);
	free(head);
	head = NULL;
}

//insert in tail
Ret dlist_insert(DList *head, int index, void *data)
{
	DList *tp, *tp1;
	int length = 0;
	int ret = RET_OK;

	return_val_if_fail(head != NULL, RET_INVALID_PARAM);
	return_val_if_fail(index <= dlist_length(head), RET_INVALID_PARAM);

#ifdef RW_LOCK
		dlist_wrlock(head);
#else
		dlist_lock(head);
#endif


	do {
		
		tp1 = get_dlist_item(head, index, 1);

		tp = (DList *)malloc(sizeof(DList));
		if(tp == NULL) {
			ret = RET_NOMEM;
			break;
		}
		
		tp->data = data;
		_dlist_add(tp, tp1->prev, tp1);
	} while(0);

	dlist_unlock(head);
	
	return ret;
}

//add in head
Ret dlist_prepend(DList *head, void *data)
{
	return dlist_insert(head, 0, data);
}

//add in tail
Ret dlist_append(DList *head, void *data)
{
	return dlist_insert(head, -1, data);	
}

Ret dlist_foreach(DList *head, DataVisitFunc visit, void *usr_data)
{
	DList *tmp = NULL;
	int ret = RET_OK;

	return_val_if_fail(head != NULL && visit != NULL, RET_INVALID_PARAM);

#ifdef RW_LOCK
		dlist_rdlock(head);
#else
		dlist_lock(head);
#endif

	
	for(tmp = head->next; tmp != head && ret != RET_STOP; tmp = tmp->next) {
		ret = visit(usr_data, tmp->data);
	}

	dlist_unlock(head);
	
	return RET_OK;
}

int dlist_find(DList *head, DataCmpFunc cmp, void *usr_data)
{
	DList *tmp = NULL;
	int i = 0;

	return_val_if_fail(head != NULL && cmp != NULL, -1);

#ifdef RW_LOCK
		dlist_rdlock(head);
#else
		dlist_lock(head);
#endif

	
	tmp = head->next;
	while(tmp != head) {
		if(cmp(usr_data, tmp->data) == 0)
			break;
		i++;
		tmp = tmp->next;
	}

	dlist_unlock(head);

	return i;
}

Ret dlist_get_by_index(DList *head, int index, void **data)
{
	DList *tmp = NULL;
	int ret = RET_OK;
	
	return_val_if_fail(head != NULL, RET_INVALID_PARAM);

#ifdef RW_LOCK
		dlist_rdlock(head);
#else
		dlist_lock(head);
#endif

	
	tmp = get_dlist_item(head, index, 0);

	if(tmp == NULL)
		ret = RET_FAIL;
	else 
		*data = tmp->data;

	dlist_unlock(head);
	
	return ret;
}

Ret dlist_set_by_index(DList *head, int index, void *data)
{
	int ret = RET_OK;
	DList *tmp = NULL;
	
	return_val_if_fail(head != NULL, RET_INVALID_PARAM);

#ifdef RW_LOCK
		dlist_wrlock(head);
#else
		dlist_lock(head);
#endif

	
	tmp = get_dlist_item(head, index, 0);

	if(tmp == NULL)
		ret = RET_FAIL;
	else 
		tmp->data = data;

	dlist_unlock(head);
	
	return ret;
}


Ret dlist_delete(DList *head, int index)
{
	DList *tp = NULL;
	
	return_val_if_fail(head != NULL && index <= dlist_length(head), RET_INVALID_PARAM);

#ifdef RW_LOCK
		dlist_wrlock(head);
#else
		dlist_lock(head);
#endif

	
	tp = get_dlist_item(head, index, 0);

	if(tp != NULL) {
		tp->next->prev = tp->prev;
		tp->prev->next = tp->next;
		free(tp);
		tp = NULL;
	}

	dlist_unlock(head);
	
	return RET_OK;
}

int dlist_length(DList *head)
{
	int i = 0;
	DList *tmp = NULL;

	return_val_if_fail(head != NULL, 0);

#ifdef RW_LOCK
		dlist_rdlock(head);
#else
		dlist_lock(head);
#endif


	tmp = head->next;

	while(tmp != head) {
		i++;
		tmp = tmp->next;
	}

	dlist_unlock(head);

	return i;
}
