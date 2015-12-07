
#include <stdio.h>

#include "matlib.h"

#define M 3
#define N 3

int main(void)
{
    struct MATLIB_t mat_a;
    struct MATLIB_t mat_b;
    struct MATLIB_t vec_a;

    float mat_a_values[M * N] = {   1, 2, 3,
                                4, 5, 6,
                                7, 8, 9};

    float mat_b_values[M][N] = {    {9, 8, 7},
                                {6, 5, 4},
                                {3, 2, 1}};

    float vec_a_values[M] = {1, 2, 3};

    matlib_create(&mat_a, mat_a_values, M, N);
    matlib_create(&mat_b, *mat_b_values, M, N);

    matlib_print(&mat_a); printf("\n");
    matlib_print(&mat_b); printf("\n");

    mat_a = matlib_multiply(&mat_a, &mat_b);
    matlib_print(&mat_a); printf("\n");

    matlib_create(&vec_a, vec_a_values, 1, M);

    matlib_print(&vec_a); printf("\n");
    vec_a = matlib_multiply(&vec_a, &mat_b);
    matlib_print(&vec_a); printf("\n");

    return 0;
}
