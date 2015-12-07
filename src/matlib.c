
#include "matlib.h"

void matlib_create(struct MATLIB_t *matrix, float *values, size_t m, size_t n)
{
    matlib_create_empty(matrix, m, n);

    /* Copy the values from in into the out matrix. */
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrix->values[i][j] = values[i * m + j];
        }
    }
}

void matlib_create_empty(struct MATLIB_t *matrix, size_t m, size_t n)
{
    matrix->values = malloc_2d(m, n, sizeof(float));
    matrix->m = m;
    matrix->n = n;
}

bool matlib_copy(struct MATLIB_t *out, struct MATLIB_t *in)
{
    if (out->m != in->m || out->n != in->n) { /* Make sure the dimensions match. */
        return false;
    }

    /* Copy the values from in into the out matrix. */
    for (int i = 0; i < in->m; i++) {
        for (int j = 0; j < in->n; j++) {
            out->values[i][j] = in->values[i][j];
        }
    }

    return true;
}

struct MATLIB_t matlib_multiply(struct MATLIB_t *a, struct MATLIB_t *b)
{
    struct MATLIB_t result;
    matlib_create_empty(&result, a->m, b->n);

    if (a->m != b->n) {
        return result;
    }

    for (int m = 0; m < a->m; m++) {
        for (int n = 0; n < a->n; n++) {
            for (int i = 0; i < a->n; i++) {
                result.values[m][n] += a->values[m][i] * b->values[i][n];
            }
        }
    }

    return result;
}

void matlib_print(struct MATLIB_t *matrix)
{
    for (int m = 0; m < matrix->m; m++) {
        for (int n = 0; n < matrix->n; n++) {
            printf("%f ", matrix->values[m][n]);
        }
        printf("\n");
    }
}

/*---------- HELPER FUNCTIONS ----------*/
static void* malloc_2d(unsigned int rows, unsigned int columns, size_t size)
{
    void **ptr_array = calloc(rows, sizeof(void *));
    if (ptr_array == NULL) {
        perror("malloc");
        return NULL;
    }

    void *data_array = calloc(rows * columns, size);
    if (data_array == NULL) {
        perror("malloc");
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        ptr_array[i] = data_array + columns * size * i;
    }

    return ptr_array;
}
