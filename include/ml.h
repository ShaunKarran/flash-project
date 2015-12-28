
#ifndef _ML_H_
#define _ML_H_

#include <math.h>
#include <stdio.h>
#include <string.h>

typedef struct Vec2_t {
    float values[2];
} vec2_t;

typedef struct Vec3_t {
    float values[3];
} vec3_t;

typedef struct Vec4_t {
    float values[4];
} vec4_t;

typedef struct Mat2_t {
    float values[2][2];
} mat2_t;

typedef struct Mat3_t {
    float values[3][3];
} mat3_t;

typedef struct Mat4_t {
    float values[4][4];
} mat4_t;

void ml_mat2_identity(mat2_t *matrix);
void ml_mat3_identity(mat3_t *matrix);
void ml_mat4_identity(mat4_t *matrix);

mat2_t ml_multiply_mat2_mat2(mat2_t *matrix_a, mat2_t *matrix_b);
mat3_t ml_multiply_mat3_mat3(mat3_t *matrix_a, mat3_t *matrix_b);
mat4_t ml_multiply_mat4_mat4(mat4_t *matrix_a, mat4_t *matrix_b);

vec3_t ml_multiply_mat3_vec3(mat3_t *matrix, vec3_t *vector);
vec4_t ml_multiply_mat4_vec4(mat4_t *matrix, vec4_t *vector);

void ml_translate(mat4_t *matrix, float x, float y, float z);
void ml_rotate_x(mat4_t *matrix, float angle);
void ml_rotate_y(mat4_t *matrix, float angle);
void ml_rotate_z(mat4_t *matrix, float angle);

void ml_print_mat2(mat2_t *matrix);
void ml_print_mat3(mat3_t *matrix);
void ml_print_mat4(mat4_t *matrix);

void ml_print_vec2(vec2_t *vector);
void ml_print_vec3(vec3_t *vector);
void ml_print_vec4(vec4_t *vector);

static float deg_to_rad(float degrees);

#endif /* _ML_H_ */
