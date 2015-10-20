#include <stdlib.h>
#include "darray.h"
#include "lcontainer.h"
#include "lcontainer_darray.h"

typedef struct _PrivInfo {
	DArray *darray;
}DarrayPrivInfo;

static Ret lcontainer_darray_insert(LContainer *me, uint index, void *data)
{
    DarrayPrivInfo *priv = (DarrayPrivInfo *)me->priv;

	return darray_insert(priv->darray, index, data);
}

static Ret lcontainer_darray_append(LContainer *me, void *data)
{
    DarrayPrivInfo *priv = (DarrayPrivInfo *)me->priv;

	return darray_append(priv->darray, data);
}

static Ret lcontainer_darray_prepend(LContainer *me, void *data)
{
    DarrayPrivInfo *priv = (DarrayPrivInfo *)me->priv;

	return darray_prepend(priv->darray, data);
}

static int lcontainer_darray_find(LContainer *me, DataCmpFunc cmp, void *usr_data)
{
    DarrayPrivInfo *priv = (DarrayPrivInfo *)me->priv;

	return darray_find(priv->darray, cmp, usr_data);
}

static Ret lcontainer_darray_foreach(LContainer *me, DataVisitFunc visit, void *usr_data)
{
    DarrayPrivInfo *priv = (DarrayPrivInfo *)me->priv;

	return darray_foreach(priv->darray, visit, usr_data);
}

static Ret lcontainer_darray_get_by_index(LContainer *me, int index, void **data)
{
    DarrayPrivInfo *priv = (DarrayPrivInfo *)me->priv;

	return darray_get_by_index(priv->darray, index, data);
}

static Ret lcontainer_darray_set_by_index(LContainer *me, int index, void *data)
{
    DarrayPrivInfo *priv = (DarrayPrivInfo *)me->priv;

	return darray_set_by_index(priv->darray, index, data);
}

static Ret lcontainer_darray_delete(LContainer *me, int index)
{
    DarrayPrivInfo *priv = (DarrayPrivInfo *)me->priv;

	return darray_delete(priv->darray, index);
}

static void lcontainer_darray_destroy(LContainer * me)
{
    DarrayPrivInfo *priv = (DarrayPrivInfo *)me->priv;

	return darray_destroy(priv->darray);
}

static int lcontainer_darray_length(LContainer *me)
{
    DarrayPrivInfo *priv = (DarrayPrivInfo *)me->priv;

	return darray_length(priv->darray);
}

LContainer *lcontainer_darray_create(void)
{
    LContainer *me = NULL;

    me = (LContainer *)malloc(sizeof(LContainer) + sizeof(DarrayPrivInfo));
    if(me != 	NULL) {
        DarrayPrivInfo *priv = (DarrayPrivInfo *)me->priv;
		
        me->insert 	     = lcontainer_darray_insert;
        me->append 	     = lcontainer_darray_append;
        me->prepend 	 = lcontainer_darray_prepend;
        me->find 		 = lcontainer_darray_find;
        me->for_each	 = lcontainer_darray_foreach;
        me->get_by_index = lcontainer_darray_get_by_index;
        me->set_by_index = lcontainer_darray_set_by_index;
        me->cdelete	     = lcontainer_darray_delete;
        me->destroy	     = lcontainer_darray_destroy;
        me->length	     = lcontainer_darray_length;

		priv->darray = darray_create();
		if(priv->darray == NULL) {
            free(me);
            me = NULL;
		}
	}

    return me;
}

