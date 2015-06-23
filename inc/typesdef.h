#ifndef TYPESDEF_H
#define TYPESDEF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

typedef enum {
	RET_OK = 0,
	RET_NOMEM,
	RET_STOP,
	RET_INVALID_PARAM,
	RET_FAIL
}Ret;

typedef int (*DataVisitFunc)(void *ctx, void *data);
typedef int (*DataCmpFunc)(void *ctx, void *data);
//typedef int (*DataDestoryFunc)(void *ctx, void *data);


#define return_if_fail(p) if(!(p)) \
	{printf("%s:%d Warning: "#p" failed.\n", \
		__func__, __LINE__); \
		return; \
	}

#define return_val_if_fail(p, ret) if(!(p)) \
	{printf("%s:%d Warning: "#p" failed.\n", \
		__func__, __LINE__); \
		return(ret); \
	}


#define is_power_of_2(x) ((x != 0) && ((x) & (x-1)))

/* swap 2 integer */
#define SWAP_INT(x,y) do{ \
				x = x^y; \
				y = x^y; \
				x = x^y; \
				}while(0)

/* basic data types */
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

#ifndef BOOL
#define BOOL uchar

#define TRUE  (1)
#define FALSE (0)
#endif


#ifdef __cplusplus
}
#endif

#endif