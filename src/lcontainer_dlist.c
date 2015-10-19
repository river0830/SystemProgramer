#include <stdlib.h>
#include "dlist.h"
#include "lcontainer_dlist.h"

typedef struct _PrivInfo {
	DList *dlist;
}DlistPrivInfo;

static Ret lcontainer_dlist_insert(LContainer *me, uint index, void *data)
{
    DlistPrivInfo *priv = (DlistPrivInfo *)me->priv;

	return dlist_insert(priv->dlist, index, data);
}

static Ret lcontainer_dlist_append(LContainer *me, void *data)
{
    DlistPrivInfo *priv = (DlistPrivInfo *)me->priv;

	return dlist_append(priv->dlist, data);
}

static Ret lcontainer_dlist_prepend(LContainer *me, void *data)
{
    DlistPrivInfo *priv = (DlistPrivInfo *)me->priv;

	return dlist_prepend(priv->dlist, data);
}

static int lcontainer_dlist_find(LContainer *me, DataCmpFunc cmp, void *usr_data)
{
    DlistPrivInfo *priv = (DlistPrivInfo *)me->priv;

	return dlist_find(priv->dlist, cmp, usr_data);
}

static Ret lcontainer_dlist_foreach(LContainer *me, DataVisitFunc visit, void *usr_data)
{
    DlistPrivInfo *priv = (DlistPrivInfo *)me->priv;

	return dlist_foreach(priv->dlist, visit, usr_data);
}

static Ret lcontainer_dlist_get_by_index(LContainer *me, int index, void **data)
{
    DlistPrivInfo *priv = (DlistPrivInfo *)me->priv;

	return dlist_get_by_index(priv->dlist, index, data);
}

static Ret lcontainer_dlist_set_by_index(LContainer *me, int index, void *data)
{
    DlistPrivInfo *priv = (DlistPrivInfo *)me->priv;

	return dlist_set_by_index(priv->dlist, index, data);
}

static Ret lcontainer_dlist_delete(LContainer *me, int index)
{
    DlistPrivInfo *priv = (DlistPrivInfo *)me->priv;

	return dlist_delete(priv->dlist, index);
}

static void lcontainer_dlist_destroy(LContainer * me)
{
    DlistPrivInfo *priv = (DlistPrivInfo *)me->priv;

	return dlist_destroy(priv->dlist);
}

static int lcontainer_dlist_length(LContainer *me)
{
    DlistPrivInfo *priv = (DlistPrivInfo *)me->priv;

	return dlist_length(priv->dlist);
}

LContainer *lcontainer_dlist_create(void)
{
    LContainer *me = NULL;

    me = (LContainer *)malloc(sizeof(LContainer) + sizeof(DlistPrivInfo));
    if(me != 	NULL) {
        DlistPrivInfo *priv = (DlistPrivInfo *)me->priv;
		
        me->insert 	     = lcontainer_dlist_insert;
        me->append 	     = lcontainer_dlist_append;
        me->prepend 	 = lcontainer_dlist_prepend;
        me->find 		 = lcontainer_dlist_find;
        me->for_each	 = lcontainer_dlist_foreach;
        me->get_by_index = lcontainer_dlist_get_by_index;
        me->set_by_index = lcontainer_dlist_set_by_index;
        me->cdelete	     = lcontainer_dlist_delete;
        me->destroy	     = lcontainer_dlist_destroy;
        me->length	     = lcontainer_dlist_length;

		priv->dlist = dlist_create(NULL);
		if(priv->dlist == NULL) {
            free(me);
            me = NULL;
		}
	}

    return me;
}


