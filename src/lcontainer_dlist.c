#include <stdlib.h>
#include "dlist.h"
#include "lcontainer_dlist.h"

typedef struct _PrivInfo {
	DList *dlist;
}DlistPrivInfo;

static Ret lcontainer_dlist_insert(LContainer *this, uint index, void *data)
{
	DlistPrivInfo *priv = (DlistPrivInfo *)this->priv;

	return dlist_insert(priv->dlist, index, data);
}

static Ret lcontainer_dlist_append(LContainer *this, void *data)
{
	DlistPrivInfo *priv = (DlistPrivInfo *)this->priv;

	return dlist_append(priv->dlist, data);
}

static Ret lcontainer_dlist_prepend(LContainer *this, void *data)
{
	DlistPrivInfo *priv = (DlistPrivInfo *)this->priv;

	return dlist_prepend(priv->dlist, data);
}

static int lcontainer_dlist_find(LContainer *this, DataCmpFunc cmp, void *usr_data)
{
	DlistPrivInfo *priv = (DlistPrivInfo *)this->priv;

	return dlist_find(priv->dlist, cmp, usr_data);
}

static Ret lcontainer_dlist_foreach(LContainer *this, DataVisitFunc visit, void *usr_data)
{
	DlistPrivInfo *priv = (DlistPrivInfo *)this->priv;

	return dlist_foreach(priv->dlist, visit, usr_data);
}

static Ret lcontainer_dlist_get_by_index(LContainer *this, int index, void **data)
{
	DlistPrivInfo *priv = (DlistPrivInfo *)this->priv;

	return dlist_get_by_index(priv->dlist, index, data);
}

static Ret lcontainer_dlist_set_by_index(LContainer *this, int index, void *data)
{
	DlistPrivInfo *priv = (DlistPrivInfo *)this->priv;

	return dlist_set_by_index(priv->dlist, index, data);
}

static Ret lcontainer_dlist_delete(LContainer *this, int index)
{
	DlistPrivInfo *priv = (DlistPrivInfo *)this->priv;

	return dlist_delete(priv->dlist, index);
}

static void lcontainer_dlist_destroy(LContainer * this)
{
	DlistPrivInfo *priv = (DlistPrivInfo *)this->priv;

	return dlist_destroy(priv->dlist);
}

static int lcontainer_dlist_length(LContainer *this)
{
	DlistPrivInfo *priv = (DlistPrivInfo *)this->priv;

	return dlist_length(priv->dlist);
}

LContainer *lcontainer_dlist_create(void)
{
	LContainer *this = NULL;

	this = (LContainer *)malloc(sizeof(LContainer) + sizeof(DlistPrivInfo));
	if(this != 	NULL) {
		DlistPrivInfo *priv = (DlistPrivInfo *)this->priv;
		
		this->insert 	= lcontainer_dlist_insert;
		this->append 	= lcontainer_dlist_append;
		this->prepend 	= lcontainer_dlist_prepend;
		this->find 		= lcontainer_dlist_find;
		this->foreach	= lcontainer_dlist_foreach;
		this->get_by_index = lcontainer_dlist_get_by_index;
		this->set_by_index = lcontainer_dlist_set_by_index;
		this->delete	= lcontainer_dlist_delete;
		this->destroy	= lcontainer_dlist_destroy;
		this->length	= lcontainer_dlist_length;

		priv->dlist = dlist_create(NULL);
		if(priv->dlist == NULL) {
			free(this);
			this = NULL;
		}
	}

	return this;
}


