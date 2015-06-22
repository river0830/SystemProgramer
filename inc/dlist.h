/*
 * File:    dlist.h
 * Author:  river
 * Brief:   circular double list header file.
 *
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
 * 2012-9-20  river created
 */
#include "typesdef.h"
#include "locker.h"
#include "rw_locker.h"
 
#ifndef DLIST_H
#define DLIST_H

#ifdef __cplusplus
extern "C" {
#endif

#define RW_LOCK

struct _DList;
typedef struct _DList DList;

#ifndef RW_LOCK
DList *dlist_create(Locker *lock);
#else
DList *dlist_create(RWLock *lock);
#endif

Ret dlist_insert(DList *head, int index, void *data);

/*add in tail*/
Ret dlist_append(DList *head, void *data);
/*add in head*/
Ret dlist_prepend(DList *head, void *data);

int dlist_find(DList *head, DataCmpFunc cmp, void *usr_data);
Ret dlist_foreach(DList *head, DataVisitFunc visit, void *usr_data);

Ret dlist_get_by_index(DList *head, int index, void **data);
Ret dlist_set_by_index(DList *head, int index, void *data);
Ret dlist_delete(DList *head, int index);

void dlist_destroy(DList *head);
int dlist_length(DList *head);

#ifdef __cplusplus
}
#endif

#endif