#include <stdlib.h>
#include "darray.h"
#include "lcontainer.h"
#include "lcontainer_darray.h"

typedef struct _PrivInfo {
	DArray *darray;
}DarrayPrivInfo;

static Ret lcontainer_darray_insert(LContainer *this, uint index, void *data)
{
	DarrayPrivInfo *priv = (DarrayPrivInfo *)this->priv;

	return darray_insert(priv->darray, index, data);
}

static Ret lcontainer_darray_append(LContainer *this, void *data)
{
	DarrayPrivInfo *priv = (DarrayPrivInfo *)this->priv;

	return darray_append(priv->darray, data);
}

static Ret lcontainer_darray_prepend(LContainer *this, void *data)
{
	DarrayPrivInfo *priv = (DarrayPrivInfo *)this->priv;

	return darray_prepend(priv->darray, data);
}

static int lcontainer_darray_find(LContainer *this, DataCmpFunc cmp, void *usr_data)
{
	DarrayPrivInfo *priv = (DarrayPrivInfo *)this->priv;

	return darray_find(priv->darray, cmp, usr_data);
}

static Ret lcontainer_darray_foreach(LContainer *this, DataVisitFunc visit, void *usr_data)
{
	DarrayPrivInfo *priv = (DarrayPrivInfo *)this->priv;

	return darray_foreach(priv->darray, visit, usr_data);
}

static Ret lcontainer_darray_get_by_index(LContainer *this, int index, void **data)
{
	DarrayPrivInfo *priv = (DarrayPrivInfo *)this->priv;

	return darray_get_by_index(priv->darray, index, data);
}

static Ret lcontainer_darray_set_by_index(LContainer *this, int index, void *data)
{
	DarrayPrivInfo *priv = (DarrayPrivInfo *)this->priv;

	return darray_set_by_index(priv->darray, index, data);
}

static Ret lcontainer_darray_delete(LContainer *this, int index)
{
	DarrayPrivInfo *priv = (DarrayPrivInfo *)this->priv;

	return darray_delete(priv->darray, index);
}

static void lcontainer_darray_destroy(LContainer * this)
{
	DarrayPrivInfo *priv = (DarrayPrivInfo *)this->priv;

	return darray_destroy(priv->darray);
}

static int lcontainer_darray_length(LContainer *this)
{
	DarrayPrivInfo *priv = (DarrayPrivInfo *)this->priv;

	return darray_length(priv->darray);
}

LContainer *lcontainer_darray_create(void)
{
	LContainer *this = NULL;

	this = (LContainer *)malloc(sizeof(LContainer) + sizeof(DarrayPrivInfo));
	if(this != 	NULL) {
		DarrayPrivInfo *priv = (DarrayPrivInfo *)this->priv;
		
		this->insert 	= lcontainer_darray_insert;
		this->append 	= lcontainer_darray_append;
		this->prepend 	= lcontainer_darray_prepend;
		this->find 		= lcontainer_darray_find;
		this->foreach	= lcontainer_darray_foreach;
		this->get_by_index = lcontainer_darray_get_by_index;
		this->set_by_index = lcontainer_darray_set_by_index;
		this->delete	= lcontainer_darray_delete;
		this->destroy	= lcontainer_darray_destroy;
		this->length	= lcontainer_darray_length;

		priv->darray = darray_create();
		if(priv->darray == NULL) {
			free(this);
			this = NULL;
		}
	}

	return this;
}

