
#include "ml.h"

void ml_mat2_identity(mat2_t *matrix)
{
    memset(matrix->values, 0, 4 * sizeof(float));
    matrix->values[0][0] = 1;
    matrix->values[1][1] = 1;
}

void ml_mat3_identity(mat3_t *matrix)
{
    memset(matrix->values, 0, 9 * sizeof(float));
    matrix->values[0][0] = 1;
    matrix->values[1][1] = 1;
    matrix->values[2][2] = 1;
}

void ml_mat4_identity(mat4_t *matrix)
{
    memset(matrix->values, 0, 16 * sizeof(float));
    matrix->values[0][0] = 1;
    matrix->values[1][1] = 1;
    matrix->values[2][2] = 1;
    matrix->values[3][3] = 1;
}

mat2_t ml_multiply_mat2_mat2(mat2_t *matrix_a, mat2_t *matrix_b)
{
    mat2_t result;

    for (int m = 0; m < 2; m++) {
        for (int n = 0; n < 2; n++) {
            result.values[m][n] =   matrix_a->values[m][0] * matrix_b->values[0][n] +
                                    matrix_a->values[m][1] * matrix_b->values[1][n];
        }
    }

    return result;
}

mat3_t ml_multiply_mat3_mat3(mat3_t *matrix_a, mat3_t *matrix_b)
{
    mat3_t result;

    for (int m = 0; m < 3; m++) {
        for (int n = 0; n < 3; n++) {
            result.values[m][n] =   matrix_a->values[m][0] * matrix_b->values[0][n] +
                                    matrix_a->values[m][1] * matrix_b->values[1][n] +
                                    matrix_a->values[m][2] * matrix_b->values[2][n];
        }
    }

    return result;
}

mat4_t ml_multiply_mat4_mat4(mat4_t *matrix_a, mat4_t *matrix_b)
{
    mat4_t result;

    for (int m = 0; m < 4; m++) {
        for (int n = 0; n < 4; n++) {
            result.values[m][n] =   matrix_a->values[m][0] * matrix_b->values[0][n] +
                                    matrix_a->values[m][1] * matrix_b->values[1][n] +
                                    matrix_a->values[m][2] * matrix_b->values[2][n] +
                                    matrix_a->values[m][3] * matrix_b->values[3][n];
        }
    }

    return result;
}

vec3_t ml_multiply_mat3_vec3(mat3_t *matrix, vec3_t *vector)
{
    vec3_t result;

    for (int m = 0; m < 3; m++) {
        result.values[m] =  matrix->values[m][0] * vector->values[0] +
                            matrix->values[m][1] * vector->values[1] +
                            matrix->values[m][2] * vector->values[2];
    }

    return result;
}

vec4_t ml_multiply_mat4_vec4(mat4_t *matrix, vec4_t *vector)
{
    vec4_t result;

    for (int m = 0; m < 4; m++) {
        result.values[m] =  matrix->values[m][0] * vector->values[0] +
                            matrix->values[m][1] * vector->values[1] +
                            matrix->values[m][2] * vector->values[2] +
                            matrix->values[m][3] * vector->values[3];
    }

    return result;
}

void ml_translate(mat4_t *matrix, float x, float y, float z)
{
    matrix->values[0][3] += x;
    matrix->values[1][3] += y;
    matrix->values[2][3] += z;
}

void ml_rotate_x(mat4_t *matrix, float angle)
{
    mat4_t rotation;
    ml_mat4_identity(&rotation);
    rotation.values[1][1] =  cos(deg_to_rad(angle));
    rotation.values[1][2] = -sin(deg_to_rad(angle));
    rotation.values[2][1] =  sin(deg_to_rad(angle));
    rotation.values[2][2] =  cos(deg_to_rad(angle));

    *matrix = ml_multiply_mat4_mat4(&rotation, matrix);
}

void ml_rotate_y(mat4_t *matrix, float angle)
{
    mat4_t rotation;
    ml_mat4_identity(&rotation);
    rotation.values[0][0] =  cos(deg_to_rad(angle));
    rotation.values[0][2] =  sin(deg_to_rad(angle));
    rotation.values[2][0] = -sin(deg_to_rad(angle));
    rotation.values[2][2] =  cos(deg_to_rad(angle));

    *matrix = ml_multiply_mat4_mat4(&rotation, matrix);
}

void ml_rotate_z(mat4_t *matrix, float angle)
{
    mat4_t rotation;
    ml_mat4_identity(&rotation);
    rotation.values[0][0] =  cos(deg_to_rad(angle));
    rotation.values[0][1] =  sin(deg_to_rad(angle));
    rotation.values[1][0] = -sin(deg_to_rad(angle));
    rotation.values[1][1] =  cos(deg_to_rad(angle));

    *matrix = ml_multiply_mat4_mat4(&rotation, matrix);
}

void ml_print_mat2(mat2_t *matrix)
{
    for (int m = 0; m < 2; m++) {
        for (int n = 0; n < 2; n++) {
            printf("%f ", matrix->values[m][n]);
        }
        printf("\n");
    }
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

void ml_print_mat4(mat4_t *matrix)
{
    for (int m = 0; m < 4; m++) {
        for (int n = 0; n < 4; n++) {
            printf("%f ", matrix->values[m][n]);
        }
        printf("\n");
    }
}

void ml_print_vec2(vec2_t *vector)
{
    for (int i = 0; i < 2; i++) {
        printf("%f ", vector->values[i]);
    }
    printf("\n");
}

void ml_print_vec3(vec3_t *vector)
{
    for (int i = 0; i < 3; i++) {
        printf("%f ", vector->values[i]);
    }
    printf("\n");
}

void ml_print_vec4(vec4_t *vector)
{
    for (int i = 0; i < 4; i++) {
        printf("%f ", vector->values[i]);
    }
    printf("\n");
}

static float deg_to_rad(float degrees)
{
    return degrees * M_PI / 180.0;
}
