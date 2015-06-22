#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "dlist.h"
#include "darray.h"
#include "lcontainer.h"
#include "lcontainer_dlist.h"
#include "lcontainer_darray.h"
#include "queue.h"
#include "test.h"

int print_int(void *ctx, void *data)
{
	printf("%d ", (int)data);
	return 0;
}

static int list_sum(void *ctx, void *data)
{
	int *tmp = (int *)ctx;

	*tmp += (int)data;
	return 0;
}

static int list_max(void *ctx, void *data)
{
	int *tmp = (int *)ctx;

	if(*tmp < (int)data)
		*tmp = (int)data;

	return 0;
}

int cmp_int(void* ctx, void* data)
{
	return (int)data - (int)ctx;
}

int cmp_int_inverse(void *ctx, void *data)
{
	return (int)ctx - (int)data;
}

static void queue_test(LContainer *this)
{
	Queue *queue = NULL;
	int i = 0, tmp = 0, n = 20;
	
	queue = queue_create(this);
	return_if_fail(queue != NULL);

	for(i = 0; i < n; i++) {
		assert(queue_push(queue, (void *)i) == RET_OK);
		assert(queue_length(queue) == (i+1));
	}

	printf("print queue \n");
	queue_foreach(queue, print_int, NULL);
	printf("\n");

	for(i = 0; i < n; i++) {
		assert(queue_head(queue, (void **)&tmp) == RET_OK);
		assert(i == tmp);
		assert(queue_length(queue) == (n-i));
		assert(queue_pop(queue) == RET_OK);
	}
	
	printf("destroy the queue and container \n");	
	queue_destroy(queue);
}

void test_container(void)
{
	LContainer *this = NULL;

	printf("***** dlist queue test ***** \n");
	this = lcontainer_dlist_create();
	return_if_fail(this != NULL);
	queue_test(this);
	printf("***** dlist queue test end *****\n");

	printf("***** darray queue test *****\n");
	this = lcontainer_darray_create();
	return_if_fail(this != NULL);
	queue_test(this);
	printf("***** darray queue test end *****\n");
}


static void test_int_dlist(void)
{
	int s = 0;
	int i = 0;
	int n = 100;
	int data = 0;
	DList* dlist = dlist_create(NULL);

	return_if_fail(dlist != NULL);
	for(i = 0; i < n; i++)
	{
		assert(dlist_append(dlist, (void*)i) == RET_OK);
		assert(dlist_length(dlist) == (i + 1));
		assert(dlist_get_by_index(dlist, i, (void**)&data) == RET_OK);
		assert(data == i);
		assert(dlist_set_by_index(dlist, i, (void*)(2*i)) == RET_OK);
		assert(dlist_get_by_index(dlist, i, (void**)&data) == RET_OK);
		assert(data == 2*i);
		assert(dlist_set_by_index(dlist, i, (void*)i) == RET_OK);
		assert(dlist_find(dlist, cmp_int, (void*)i) == i);
	}

	dlist_foreach(dlist, print_int, NULL);
	printf("\n");
	
	for(i = 0; i < n; i++)
	{
		assert(dlist_get_by_index(dlist, 0, (void**)&data) == RET_OK);
		assert(data == (i));
		assert(dlist_length(dlist) == (n-i));
		assert(dlist_delete(dlist, 0) == RET_OK);
		assert(dlist_length(dlist) == (n-i-1));
		if((i + 1) < n)
		{
			assert(dlist_get_by_index(dlist, 0, (void**)&data) == RET_OK);
			assert((int)data == (i+1));
		}
	}
	
	assert(dlist_length(dlist) == 0);

	for(i = 0; i < n; i++)
	{
		assert(dlist_prepend(dlist, (void*)i) == RET_OK);
		assert(dlist_length(dlist) == (i + 1));
		assert(dlist_get_by_index(dlist, 0, (void**)&data) == RET_OK);
		assert(data == i);
		assert(dlist_set_by_index(dlist, 0, (void*)(2*i)) == RET_OK);
		assert(dlist_get_by_index(dlist, 0, (void**)&data) == RET_OK);
		assert(data == 2*i);
		assert(dlist_set_by_index(dlist, 0, (void*)i) == RET_OK);
	}

	//i = n - 1;
	//assert(dlist_foreach(dlist, check_and_dec_int, &i) == RET_OK);
	
	s = dlist_length(dlist);
	for(i = 1; i < n; i++)
	{
		assert(dlist_insert(dlist, i, (void*)i) == RET_OK);
		assert(dlist_length(dlist) == (s + i));
		assert(dlist_get_by_index(dlist, i, (void**)&data) == RET_OK);
		assert(data == i);
		assert(dlist_set_by_index(dlist, i, (void*)(2*i)) == RET_OK);
		assert(dlist_get_by_index(dlist, i, (void**)&data) == RET_OK);
		assert(data == 2*i);
		assert(dlist_set_by_index(dlist, i, (void*)i) == RET_OK);
	}

	dlist_destroy(dlist);

	return;
}

static void test_list_invalid_params(void)
{
	printf("===========List test, Warning is normal begin==============\n");
	assert(dlist_length(NULL) == 0);
	assert(dlist_prepend(NULL, 0) == RET_INVALID_PARAM);
	assert(dlist_append(NULL, 0) == RET_INVALID_PARAM);
	assert(dlist_delete(NULL, 0) == RET_INVALID_PARAM);
	assert(dlist_insert(NULL, 0, 0) == RET_INVALID_PARAM);
	assert(dlist_set_by_index(NULL, 0, 0) == RET_INVALID_PARAM);
	assert(dlist_get_by_index(NULL, 0, NULL) == RET_INVALID_PARAM);
	assert(dlist_find(NULL, NULL, NULL) < 0);
	assert(dlist_foreach(NULL, NULL, NULL) == RET_INVALID_PARAM);
	printf("===========List test, Warning is normal end==============\n");

	return;
}

static Ret bubble_sort(void **data, int n, DataCmpFunc cmp)
{
	int i = 0, j = 0, excharge = 1;
	void *tmp;

	return_val_if_fail(data != NULL && cmp != NULL, RET_INVALID_PARAM);
	
	for(i = 0; (i < n-1) && excharge; i++) {
		excharge = 0;
		for(j = 0; j < n-1-i; j++) {
			if(cmp(data[j+1], data[j]) > 0) {
				tmp = data[j];
				data[j] = data[j+1];
				data[j+1] = tmp;
				excharge = 1;
			}
		}
	}

	return RET_OK;
}

static void test_array_invalid_params(void)
{
	printf("===========DArray test, Warning is normal begin==============\n");
	assert(darray_length(NULL) == 0);
	assert(darray_prepend(NULL, 0) == RET_INVALID_PARAM);
	assert(darray_append(NULL, 0) == RET_INVALID_PARAM);
	assert(darray_delete(NULL, 0) == RET_INVALID_PARAM);
	assert(darray_insert(NULL, 0, 0) == RET_INVALID_PARAM);
	assert(darray_set_by_index(NULL, 0, 0) == RET_INVALID_PARAM);
	assert(darray_get_by_index(NULL, 0, NULL) == RET_INVALID_PARAM);
	assert(darray_find(NULL, NULL, NULL) < 0);
	assert(darray_foreach(NULL, NULL, NULL) == RET_INVALID_PARAM);
	printf("===========DArray test, Warning is normal end==============\n");

	return;
}

static void test_int_darray(void)
{
	int s = 0;
	int i = 0;
	int n = 100;
	int data = 0;
	DArray* darray = darray_create();

	return_if_fail(darray != NULL);

	for(i = 0; i < n; i++)
	{
		assert(darray_append(darray, (void*)i) == RET_OK);
		assert(darray_length(darray) == (i + 1));
		assert(darray_get_by_index(darray, i, (void**)&data) == RET_OK);
		assert(data == i);
		assert(darray_set_by_index(darray, i, (void*)(2*i)) == RET_OK);
		assert(darray_get_by_index(darray, i, (void**)&data) == RET_OK);
		assert(data == 2*i);
		assert(darray_set_by_index(darray, i, (void*)i) == RET_OK);
		assert(darray_find(darray, cmp_int, (void*)i) == i);
	}
	
	for(i = 0; i < n; i++)
	{
		assert(darray_get_by_index(darray, 0, (void**)&data) == RET_OK);
		assert(data == (i));
		assert(darray_length(darray) == (n-i));
		assert(darray_delete(darray, 0) == RET_OK);
		assert(darray_length(darray) == (n-i-1));
		if((i + 1) < n)
		{
			assert(darray_get_by_index(darray, 0, (void**)&data) == RET_OK);
			assert((int)data == (i+1));
		}
	}
	
	assert(darray_length(darray) == 0);

	for(i = 0; i < n; i++)
	{
		assert(darray_prepend(darray, (void*)i) == RET_OK);
		assert(darray_length(darray) == (i + 1));
		assert(darray_get_by_index(darray, 0, (void**)&data) == RET_OK);
		assert(data == i);
		assert(darray_set_by_index(darray, 0, (void*)(2*i)) == RET_OK);
		assert(darray_get_by_index(darray, 0, (void**)&data) == RET_OK);
		assert(data == 2*i);
		assert(darray_set_by_index(darray, 0, (void*)i) == RET_OK);
	}

	//i = n - 1;
	//assert(darray_foreach(darray, check_and_dec_int, &i) == RET_OK);
	
	s = darray_length(darray);
	for(i = 1; i < n; i++)
	{
		assert(darray_insert(darray, i, (void*)i) == RET_OK);
		assert(darray_length(darray) == (s + i));
		assert(darray_get_by_index(darray, i, (void**)&data) == RET_OK);
		assert(data == i);
		assert(darray_set_by_index(darray, i, (void*)(2*i)) == RET_OK);
		assert(darray_get_by_index(darray, i, (void**)&data) == RET_OK);
		assert(data == 2*i);
		assert(darray_set_by_index(darray, i, (void*)i) == RET_OK);
	}

	printf("the before sort array: \n");
	darray_foreach(darray, print_int, NULL);
	printf("\n");

	assert(darray_sort(darray, bubble_sort, cmp_int) == RET_OK);

	printf("the up sorted array: \n");
	darray_foreach(darray, print_int, NULL);
	printf("\n");

	darray_sort(darray, bubble_sort, cmp_int_inverse);

	printf("the down sorted array: \n");
	darray_foreach(darray, print_int, NULL);
	printf("\n");

	darray_destroy(darray);

	return;
}


void test(void)
{
	test_list_invalid_params();
	test_int_dlist();

	test_array_invalid_params();
	test_int_darray();
}

