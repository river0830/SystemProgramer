/*
 * File:    darray.h
 * Author:  river
 * Brief:   dynamic array header file.
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
 * 2012-9-22  river created
 */
#include "typesdef.h"

#ifndef DARRAY_H
#define DARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

struct _DArray;
typedef struct _DArray DArray;

typedef Ret (*SortFunc)(void **array, int n, DataCmpFunc cmp);


DArray *darray_create(void);
Ret darray_insert(DArray *this, uint index, void *data);

/*add in tail*/
Ret darray_append(DArray *this, void *data);
/*add in head*/
Ret darray_prepend(DArray *this, void *data);

int darray_find(DArray *this, DataCmpFunc cmp, void *usr_data);
Ret darray_foreach(DArray *this, DataVisitFunc visit, void *usr_data);
Ret darray_sort(DArray *this, SortFunc sort, DataCmpFunc cmp);

Ret darray_get_by_index(DArray *this, int index, void **data);
Ret darray_set_by_index(DArray *this, int index, void *data);
Ret darray_delete(DArray *this, uint index);

void darray_destroy(DArray *this);
int darray_length(DArray *this);

#ifdef __cplusplus
}
#endif

#endif

