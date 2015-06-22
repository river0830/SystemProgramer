/*
 * File:  lcontainer.h
 * Author: riever
 * Brief: a simple linear container

 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
 
/*
 * History:
 * 2012-9-26 River created
 */

#ifndef LCONTAINER_H
#define LCONTAINER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "typesdef.h"

struct _LContainer;
typedef struct _LContainer LContainer;

typedef Ret (*LContainerInsert)(LContainer *this, uint index, void *data);
typedef Ret (*LContainerAppend)(LContainer *this, void *data);
typedef Ret (*LContainerPrepend)(LContainer *this, void *data);
typedef int (*LContainerFind)(LContainer *this, DataCmpFunc cmp, void *usr_data);
typedef Ret (*LContainerForeach)(LContainer *this, DataVisitFunc visit, void *usr_data);
typedef Ret (*LContainerGetByIndex)(LContainer *this, int index, void **data);
typedef Ret (*LContainerSetByIndex)(LContainer *this, int index, void *data);
typedef Ret (*LContainerDelete)(LContainer *this, int index);
typedef void (*LContainerDestroy)(LContainer *this);
typedef int (*LContainerLength)(LContainer *this);

struct _LContainer {
	LContainerInsert 		insert;
	LContainerAppend 		append;
	LContainerPrepend 		prepend;
	LContainerFind 			find;
	LContainerForeach 		foreach;
	LContainerGetByIndex 	get_by_index;
	LContainerSetByIndex 	set_by_index;
	LContainerDelete 		delete;
	LContainerDestroy 		destroy;
	LContainerLength 		length;
	
	char priv[0];
};

static inline Ret lcontainer_insert(LContainer *this, uint index, void *data)
{
	return_val_if_fail(this != NULL && this->insert != NULL, RET_INVALID_PARAM);
	
	return this->insert(this, index, data);
}

static inline Ret lcontainer_append(LContainer *this, void *data)
{
	return_val_if_fail(this != NULL && this->append != NULL, RET_INVALID_PARAM);
	
	return this->append(this, data);
}

static inline Ret lcontainer_prepend(LContainer *this, void *data)
{
	return_val_if_fail(this != NULL && this->prepend != NULL, RET_INVALID_PARAM);
	
	return this->prepend(this, data);
}

static inline int lcontainer_find(LContainer *this, DataCmpFunc cmp, void *usr_data)
{
	return_val_if_fail(this != NULL && this->find != NULL, -1);
	
	return this->find(this, cmp, usr_data);
}

static inline Ret lcontainer_foreach(LContainer *this, DataVisitFunc visit, void *usr_data)
{
	return_val_if_fail(this != NULL && this->foreach != NULL, RET_INVALID_PARAM);
	
	return this->foreach(this, visit, usr_data);
}

static inline Ret lcontainer_get_by_index(LContainer *this, int index, void **data)
{
	return_val_if_fail(this != NULL && this->get_by_index!= NULL, RET_INVALID_PARAM);
	
	return this->get_by_index(this, index, data);
}

static inline Ret lcontainer_set_by_index(LContainer *this, int index, void *data)
{
	return_val_if_fail(this != NULL && this->set_by_index!= NULL, RET_INVALID_PARAM);
	
	return this->set_by_index(this, index, data);
}

static inline Ret lcontainer_delete(LContainer *this, int index)
{
	return_val_if_fail(this != NULL && this->delete!= NULL, RET_INVALID_PARAM);
	
	return this->delete(this, index);
}

static inline void lcontainer_destroy(LContainer *this)
{
	return_if_fail(this != NULL && this->destroy != NULL);

	return this->destroy(this);
}

static inline int lcontainer_length(LContainer *this)
{
	return_val_if_fail(this != NULL && this->length != NULL, 0);

	return this->length(this);
}

#ifdef __cplusplus
}
#endif

#endif

