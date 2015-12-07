
#ifndef _MATLIB_H_
#define _MATLIB_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct MATLIB_t {
    float **values;
    size_t m; /* rows */
    size_t n; /* columns */
};

void matlib_create(struct MATLIB_t *matrix, float *values, size_t m, size_t n);

void matlib_create_empty(struct MATLIB_t *matrix, size_t m, size_t n);

bool matlib_copy(struct MATLIB_t *out, struct MATLIB_t *in);

struct MATLIB_t matlib_multiply(struct MATLIB_t *a, struct MATLIB_t *b);

void matlib_print(struct MATLIB_t *matrix);

/*---------- HELPER FUNCTIONS ----------*/
static void* malloc_2d(unsigned int rows, unsigned int columns, size_t size);

#endif /* _MATLIB_H_ */
