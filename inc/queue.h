/*
 * File: queue.h
 * Author: river
 * Brief: queue head file

 * This program is distributed in hope that it will be useful,
 * but WITHOUT ANY WARRANTY.

 * History:
 * 2012-9-26 river created
 */

#ifndef QUEUE_H
#define QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "typesdef.h"
#include "lcontainer.h"

struct _Queue;
typedef struct _Queue Queue;

Queue *queue_create(LContainer *container);
Ret queue_head(Queue *this, void **data);
Ret queue_push(Queue *this, void *data);
Ret queue_pop(Queue *this);
Ret queue_foreach(Queue *this, DataVisitFunc visit, void *data);
int queue_length(Queue *this);
void queue_destroy(Queue *this);


#ifdef __cplusplus
}
#endif

#endif
