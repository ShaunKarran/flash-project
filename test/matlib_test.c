
#include <stdio.h>

#include "ml.h"

#define M 3
#define N 3

int main(void)
{
    mat3_t mat_a;
    mat3_t mat_b;
    vec3_t vec_a;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat_a.values[i][j] = i * 3 + j + 1;
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat_b.values[i][j] = 9 - (i * 3 + j);
        }
    }
    for (int i = 0; i < 3; i++) {
        vec_a.values[i] = i + 1;
    }

    ml_print_mat3(&mat_a); printf("\n");
    ml_print_vec3(&vec_a); printf("\n");

    vec_a = ml_multiply_mat3_vec3(&mat_a, &vec_a);
    ml_print_vec3(&vec_a); printf("\n");

    mat_a = ml_multiply_mat3_mat3(&mat_a, &mat_b);
    ml_print_mat3(&mat_a); printf("\n");

    return 0;
}
