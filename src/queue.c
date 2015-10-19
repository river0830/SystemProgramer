#include <stdlib.h>
#include "queue.h"

struct _Queue {
	LContainer *lcontainer;
};

Queue *queue_create(LContainer *container)
{
    Queue *me = NULL;

	return_val_if_fail(container != NULL, NULL);

    me = (Queue *)malloc(sizeof(Queue));
    if(me != NULL) {
        me->lcontainer = container;
	}

    return me;
}

Ret queue_head(Queue *me, void **data)
{
    return_val_if_fail(me != NULL, RET_INVALID_PARAM);

    return lcontainer_get_by_index(me->lcontainer, 0, data);
}

Ret queue_pop(Queue *me)
{
    return_val_if_fail(me != NULL, RET_INVALID_PARAM);

    return lcontainer_delete(me->lcontainer, 0);
}

Ret queue_push(Queue *me, void *data)
{
    return_val_if_fail(me != NULL, RET_INVALID_PARAM);

    return lcontainer_append(me->lcontainer, data);
}

Ret queue_foreach(Queue *me, DataVisitFunc visit, void *usr_data)
{
    return_val_if_fail(me != NULL && visit != NULL, RET_INVALID_PARAM);

    return lcontainer_foreach(me->lcontainer, visit, usr_data);
}

int queue_length(Queue *me)
{
    return_val_if_fail(me != NULL, 0);

    return lcontainer_length(me->lcontainer);
}

void queue_destroy(Queue *me)
{
    if(me != NULL) {
        lcontainer_destroy(me->lcontainer);
        me->lcontainer = NULL;
        free(me);
        me = NULL;
	}
}

