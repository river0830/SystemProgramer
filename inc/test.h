/*
 * File: test.h
 * Author: river
 * Brief: the test head file

 * This program is distributed in hope that it will be useful,
 * but WITHOUT ANY WARRANTY.

 * History:
 * 2012-9-28 river created
 */
#ifndef TEST_H
#define TEST_H

#ifdef __cplusplus
extern "C" {
#endif

extern int print_int(void *ctx, void *data);
extern int cmp_int(void* ctx, void* data);
extern int cmp_int_inverse(void *ctx, void *data);

extern void test_container(void);
extern void test(void);
extern void test_pthread(void);


#ifdef __cplusplus
}
#endif

#endif
