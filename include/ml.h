
#ifndef _ML_H_
#define _ML_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Mat3_t {
    float values[3][3];
} mat3_t;

typedef struct Vec3_t {
    float values[3];
} vec3_t;

void ml_mat3_identity(mat3_t *matrix);

vec3_t ml_multiply_mat3_vec3(mat3_t *matrix, vec3_t *vector);

mat3_t ml_multiply_mat3_mat3(mat3_t *matrix_a, mat3_t *matrix_b);

void ml_print_mat3(mat3_t *matrix);

void ml_print_vec3(vec3_t *vector);

#endif /* _ML_H_ */
