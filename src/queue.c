#include <stdlib.h>
#include "queue.h"

struct _Queue {
	LContainer *lcontainer;
};

Queue *queue_create(LContainer *container)
{
	Queue *this = NULL;

	return_val_if_fail(container != NULL, NULL);

	this = (Queue *)malloc(sizeof(Queue));
	if(this != NULL) {
		this->lcontainer = container;
	}

	return this;
}

Ret queue_head(Queue *this, void **data)
{
	return_val_if_fail(this != NULL, RET_INVALID_PARAM);

	return lcontainer_get_by_index(this->lcontainer, 0, data);
}

Ret queue_pop(Queue *this)
{
	return_val_if_fail(this != NULL, RET_INVALID_PARAM);

	return lcontainer_delete(this->lcontainer, 0);
}

Ret queue_push(Queue *this, void *data)
{
	return_val_if_fail(this != NULL, RET_INVALID_PARAM);

	return lcontainer_append(this->lcontainer, data);
}

Ret queue_foreach(Queue *this, DataVisitFunc visit, void *usr_data)
{
	return_val_if_fail(this != NULL && visit != NULL, RET_INVALID_PARAM);

	return lcontainer_foreach(this->lcontainer, visit, usr_data);
}

int queue_length(Queue *this)
{
	return_val_if_fail(this != NULL, 0);

	return lcontainer_length(this->lcontainer);
}

void queue_destroy(Queue *this)
{
	if(this != NULL) {
		lcontainer_destroy(this->lcontainer);
		this->lcontainer = NULL;
		free(this);
		this = NULL;
	}
}

