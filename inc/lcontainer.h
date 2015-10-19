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

typedef Ret (*LContainerInsert)(LContainer *me, uint index, void *data);
typedef Ret (*LContainerAppend)(LContainer *me, void *data);
typedef Ret (*LContainerPrepend)(LContainer *me, void *data);
typedef int (*LContainerFind)(LContainer *me, DataCmpFunc cmp, void *usr_data);
typedef Ret (*LContainerForeach)(LContainer *me, DataVisitFunc visit, void *usr_data);
typedef Ret (*LContainerGetByIndex)(LContainer *me, int index, void **data);
typedef Ret (*LContainerSetByIndex)(LContainer *me, int index, void *data);
typedef Ret (*LContainerDelete)(LContainer *me, int index);
typedef void (*LContainerDestroy)(LContainer *me);
typedef int (*LContainerLength)(LContainer *me);

struct _LContainer {
	LContainerInsert 		insert;
	LContainerAppend 		append;
	LContainerPrepend 		prepend;
	LContainerFind 			find;
    LContainerForeach 		for_each;
	LContainerGetByIndex 	get_by_index;
	LContainerSetByIndex 	set_by_index;
    LContainerDelete 		cdelete;
	LContainerDestroy 		destroy;
	LContainerLength 		length;
	
	char priv[0];
};

static inline Ret lcontainer_insert(LContainer *me, uint index, void *data)
{
    return_val_if_fail(me != NULL && me->insert != NULL, RET_INVALID_PARAM);
	
    return me->insert(me, index, data);
}

static inline Ret lcontainer_append(LContainer *me, void *data)
{
    return_val_if_fail(me != NULL && me->append != NULL, RET_INVALID_PARAM);
	
    return me->append(me, data);
}

static inline Ret lcontainer_prepend(LContainer *me, void *data)
{
    return_val_if_fail(me != NULL && me->prepend != NULL, RET_INVALID_PARAM);
	
    return me->prepend(me, data);
}

static inline int lcontainer_find(LContainer *me, DataCmpFunc cmp, void *usr_data)
{
    return_val_if_fail(me != NULL && me->find != NULL, -1);
	
    return me->find(me, cmp, usr_data);
}

static inline Ret lcontainer_foreach(LContainer *me, DataVisitFunc visit, void *usr_data)
{
    return_val_if_fail(me != NULL && me->for_each != NULL, RET_INVALID_PARAM);
	
    return me->for_each(me, visit, usr_data);
}

static inline Ret lcontainer_get_by_index(LContainer *me, int index, void **data)
{
    return_val_if_fail(me != NULL && me->get_by_index!= NULL, RET_INVALID_PARAM);
	
    return me->get_by_index(me, index, data);
}

static inline Ret lcontainer_set_by_index(LContainer *me, int index, void *data)
{
    return_val_if_fail(me != NULL && me->set_by_index!= NULL, RET_INVALID_PARAM);
	
    return me->set_by_index(me, index, data);
}

static inline Ret lcontainer_delete(LContainer *me, int index)
{
    return_val_if_fail(me != NULL && me->cdelete!= NULL, RET_INVALID_PARAM);
	
    return me->cdelete(me, index);
}

static inline void lcontainer_destroy(LContainer *me)
{
    return_if_fail(me != NULL && me->destroy != NULL);

    return me->destroy(me);
}

static inline int lcontainer_length(LContainer *me)
{
    return_val_if_fail(me != NULL && me->length != NULL, 0);

    return me->length(me);
}

#ifdef __cplusplus
}
#endif

#endif

