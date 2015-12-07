
#include "ml.h"

void ml_mat3_identity(mat3_t *matrix)
{
    for (int m = 0; m < 3; m++) {
        for (int n = 0; n < 3; n++) {
            if (m == n) {
                matrix->values[m][n] = 1;
            } else {
                matrix->values[m][n] = 0;
            }
        }
    }
}

vec3_t ml_multiply_mat3_vec3(mat3_t *matrix, vec3_t *vector)
{
    vec3_t result;

    for (int m = 0; m < 3; m++) {
        result.values[m] = 0;

        for (int n = 0; n < 3; n++) {
            result.values[m] += matrix->values[m][n] * vector->values[n];
        }
    }

    return result;
}

mat3_t ml_multiply_mat3_mat3(mat3_t *matrix_a, mat3_t *matrix_b)
{
    mat3_t result;

    for (int m = 0; m < 3; m++) {
        for (int n = 0; n < 3; n++) {
            result.values[m][n] = 0;

            for (int i = 0; i < 3; i++) {
                result.values[m][n] += matrix_a->values[m][i] * matrix_b->values[i][n];
            }
        }
    }

    return result;
}

void ml_print_mat3(mat3_t *matrix)
{
    for (int m = 0; m < 3; m++) {
        for (int n = 0; n < 3; n++) {
            printf("%f ", matrix->values[m][n]);
        }
        printf("\n");
    }
}

void ml_print_vec3(vec3_t *vector)
{
    for (int i = 0; i < 3; i++) {
        printf("%f ", vector->values[i]);
    }
    printf("\n");
}
