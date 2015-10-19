#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "darray.h"

struct _DArray {
	void **data;
    unsigned int alloc_size;		//DArray allocate size
    unsigned int size;				//darray size
};

#define MIN_DARRAY_ALLOC_SIZE 10

/* expand 1.5 allocate size */
static Ret darray_expand(DArray *me, int size)
{
	int alloc_size = me->alloc_size + (me->alloc_size >> 1) + MIN_DARRAY_ALLOC_SIZE;
	void **data;
	
	return_val_if_fail(me != NULL, RET_INVALID_PARAM);

	if((me->size + size) > me->alloc_size) {
		data = (void **)realloc(me->data, sizeof(void *) * alloc_size);
		if(data != NULL) {
			printf("expand darray, darray size is %d, allocate size is %d \n", me->size, alloc_size);
			me->data = data;
			me->alloc_size = alloc_size;
		}
	}

	return ((me->size + size) > me->alloc_size) ? RET_FAIL : RET_OK;
}

/*
 * if the size of array less than 10, maybe not shrink
 */
static Ret darray_shrink(DArray *me)
{
	void **data;
	int alloc_size = me->size + (me->size >> 1);
	
	return_val_if_fail(me != NULL, RET_INVALID_PARAM);
	if((me->size < (me->alloc_size >> 1)) 
		&& (me->alloc_size > MIN_DARRAY_ALLOC_SIZE)) {
		data = (void **)realloc(me->data, sizeof(void *) * alloc_size);
		if(data != NULL) {
			printf("shrink darray, darray size is %d, allocate size is %d \n", me->size, alloc_size);
			me->data = data;
			me->alloc_size = alloc_size;
		}
	}

	return RET_OK;
}
		
int darray_length(DArray *me)
{
	return_val_if_fail(me != NULL, 0);

	return me->size;
}

void darray_destroy(DArray *me)
{
	return_if_fail(me != NULL);

	if(NULL != me->data) {
		free(me->data);
		me->data = NULL;
	}

	free(me);
	me = NULL;
}

Ret darray_delete(DArray *me, uint index)
{
    uint i = 0;
	
	return_val_if_fail(me != NULL && index < me->size, RET_INVALID_PARAM);

	for(i = index; i < me->size - 1; i++)
		me->data[i] = me->data[i+1];		//pointer assign
	me->size--;
	darray_shrink(me);

	return RET_OK;
}

DArray *darray_create(void)
{
	DArray *me = NULL;

	me = (DArray *)malloc(sizeof(DArray));
	return_val_if_fail(me != NULL, NULL);
	memset(me, 0, sizeof(DArray));

	return me;
}

Ret darray_insert(DArray *me, uint index, void *data)
{
	int i = 0, cnt = 0;
	Ret ret = RET_NOMEM;
	
	return_val_if_fail(me != NULL,RET_INVALID_PARAM);
	
	cnt = index <= me->size ? index : me->size;
	if(darray_expand(me, 1) == RET_OK) {
		for(i = me->size; i > cnt; i--)
			me->data[i] = me->data[i-1];
		me->data[cnt] = data;
		me->size += 1;
		ret = RET_OK;
	} 

	return ret;
}

Ret darray_append(DArray *me, void *data)
{
	return_val_if_fail(me != NULL, RET_INVALID_PARAM);

	return darray_insert(me, me->size, data);
}

Ret darray_prepend(DArray *me, void *data)
{
	return_val_if_fail(me != NULL, RET_INVALID_PARAM);

	return darray_insert(me, 0, data);
}	

Ret darray_get_by_index(DArray *me, uint index, void **data)
{
	return_val_if_fail(me != NULL && index < me->size, RET_INVALID_PARAM);

	*data = me->data[index];
	return RET_OK;
}

Ret darray_set_by_index(DArray *me, uint index, void *data)
{
	return_val_if_fail(me != NULL && index < me->size, RET_INVALID_PARAM);

	me->data[index] = data;
	return RET_OK;
}

int darray_find(DArray *me, DataCmpFunc cmp, void *usr_data)
{
    uint i = 0;
	
	return_val_if_fail(me != NULL && cmp != NULL, -1);
	for(i = 0; i < me->size; i++) 
		if(cmp(usr_data, me->data[i]) == 0)
			break;

	return i;
}
		
Ret darray_foreach(DArray *me, DataVisitFunc visit, void *usr_data)
{
    uint i = 0;
	int ret = RET_OK;

	return_val_if_fail(me!=NULL && visit!=NULL, RET_INVALID_PARAM);
	for(i = 0; i < me->size && ret != RET_STOP; i++)
		ret = visit(usr_data, me->data[i]);

	return ret;
}

Ret darray_sort(DArray *me, SortFunc sort, DataCmpFunc cmp)
{
	return_val_if_fail(me!=NULL && sort!=NULL && cmp!=NULL, RET_INVALID_PARAM);

	return sort(me->data, me->size, cmp);
}

