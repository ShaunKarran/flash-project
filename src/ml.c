
#include "ml.h"

void ml_mat2_identity(float mat[][2])
{
    memset(mat, 0, 4 * sizeof(float));
    mat[0][0] = 1; mat[1][1] = 1;
}

void ml_mat3_identity(float mat[][3])
{
    memset(mat, 0, 9 * sizeof(float));
    mat[0][0] = 1; mat[1][1] = 1; mat[2][2] = 1;
}

void ml_mat4_identity(float mat[][4])
{
    memset(mat, 0, 16 * sizeof(float));
    mat[0][0] = 1; mat[1][1] = 1; mat[2][2] = 1; mat[3][3] = 1;
    // mat[0][0] = 1; mat[0][1] = 0; mat[0][2] = 0; mat[0][3] = 0;
    // mat[1][0] = 0; mat[1][1] = 1; mat[1][2] = 0; mat[1][3] = 0;
    // mat[2][0] = 0; mat[2][1] = 0; mat[2][2] = 1; mat[2][3] = 0;
    // mat[3][0] = 0; mat[3][1] = 0; mat[3][2] = 0; mat[3][3] = 1;
}

void ml_multiply_mat2_mat2(float mat_a[][2], float mat_b[][2], float out[][2])
{
    float temp[2][2];

    temp[0][0] = mat_a[0][0] * mat_b[0][0] + mat_a[0][1] * mat_b[1][0];
    temp[0][1] = mat_a[0][0] * mat_b[0][1] + mat_a[0][1] * mat_b[1][1];
    temp[1][0] = mat_a[1][0] * mat_b[0][0] + mat_a[1][1] * mat_b[1][0];
    temp[1][1] = mat_a[1][0] * mat_b[0][1] + mat_a[1][1] * mat_b[1][1];

    out[0][0] = temp[0][0];
    out[0][1] = temp[0][1];
    out[1][0] = temp[1][0];
    out[1][1] = temp[1][1];
}

void ml_multiply_mat3_mat3(float mat_a[][3], float mat_b[][3], float out[][3])
{
    float temp[3][3];

    for (int m = 0; m < 3; m++) {
        for (int n = 0; n < 3; n++) {
            temp[m][n] = mat_a[m][0] * mat_b[0][n] + mat_a[m][1] * mat_b[1][n] + mat_a[m][2] * mat_b[2][n];
        }
    }

    for (int m = 0; m < 3; m++) {
        for (int n = 0; n < 3; n++) {
            out[m][n] = temp[m][n];
        }
    }
}

void ml_multiply_mat4_mat4(float mat_a[][4], float mat_b[][4], float out[][4])
{
    float temp[4][4];

    for (int m = 0; m < 4; m++) {
        for (int n = 0; n < 4; n++) {
            temp[m][n] =    mat_a[m][0] * mat_b[0][n] +
                            mat_a[m][1] * mat_b[1][n] +
                            mat_a[m][2] * mat_b[2][n] +
                            mat_a[m][3] * mat_b[3][n];
        }
    }

    for (int m = 0; m < 4; m++) {
        for (int n = 0; n < 4; n++) {
            out[m][n] = temp[m][n];
        }
    }
}

void ml_multiply_mat3_vec3(float mat[][3], float vec[3], float out[3])
{
    float temp[3];

    temp[0] = mat[0][0] * vec[0] + mat[0][1] * vec[1] + mat[0][2] * vec[2];
    temp[1] = mat[1][0] * vec[0] + mat[1][1] * vec[1] + mat[1][2] * vec[2];
    temp[2] = mat[2][0] * vec[0] + mat[2][1] * vec[1] + mat[2][2] * vec[2];

    out[0] = temp[0];
    out[1] = temp[1];
    out[2] = temp[2];
}

void ml_multiply_mat4_vec4(float mat[][4], float vec[4], float out[4])
{
    float temp[4];

    temp[0] = mat[0][0] * vec[0] + mat[0][1] * vec[1] + mat[0][2] * vec[2] + mat[0][3] * vec[3];
    temp[1] = mat[1][0] * vec[0] + mat[1][1] * vec[1] + mat[1][2] * vec[2] + mat[1][3] * vec[3];
    temp[2] = mat[2][0] * vec[0] + mat[2][1] * vec[1] + mat[2][2] * vec[2] + mat[2][3] * vec[3];
    temp[3] = mat[3][0] * vec[0] + mat[3][1] * vec[1] + mat[3][2] * vec[2] + mat[3][3] * vec[3];

    out[0] = temp[0];
    out[1] = temp[1];
    out[2] = temp[2];
    out[3] = temp[3];
}

void ml_translate(float mat[][4], float x, float y, float z)
{
    mat[0][3] += x;
    mat[1][3] += y;
    mat[2][3] += z;
}

void ml_rotate_x(float mat[][4], float angle)
{
    float rotation[4][4];
    float c, s;

    ml_mat4_identity(rotation);
    c = cos(deg_to_rad(angle));
    s = sin(deg_to_rad(angle));
    rotation[1][1] =  c;
    rotation[1][2] = -s;
    rotation[2][1] =  s;
    rotation[2][2] =  c;

    ml_multiply_mat4_mat4(rotation, mat, mat);
}

void ml_rotate_y(float mat[][4], float angle)
{
    float rotation[4][4];
    float c, s;

    ml_mat4_identity(rotation);
    c = cos(deg_to_rad(angle));
    s = sin(deg_to_rad(angle));
    rotation[0][0] =  c;
    rotation[0][2] =  s;
    rotation[2][0] = -s;
    rotation[2][2] =  c;

    ml_multiply_mat4_mat4(rotation, mat, mat);
}

void ml_rotate_z(float mat[][4], float angle)
{
    float rotation[4][4];
    float c, s;

    ml_mat4_identity(rotation);
    c = cos(deg_to_rad(angle));
    s = sin(deg_to_rad(angle));
    rotation[0][0] =  c;
    rotation[0][1] =  s;
    rotation[1][0] = -s;
    rotation[1][1] =  c;

    ml_multiply_mat4_mat4(rotation, mat, mat);
}

void ml_print_mat2(float mat[][2])
{
    for (int m = 0; m < 2; m++) {
        for (int n = 0; n < 2; n++) {
            printf("%f ", mat[m][n]);
        }
        printf("\n");
    }
}

void ml_print_mat3(float mat[][3])
{
    for (int m = 0; m < 3; m++) {
        for (int n = 0; n < 3; n++) {
            printf("%f ", mat[m][n]);
        }
        printf("\n");
    }
}

void ml_print_mat4(float mat[][4])
{
    for (int m = 0; m < 4; m++) {
        for (int n = 0; n < 4; n++) {
            printf("%f ", mat[m][n]);
        }
        printf("\n");
    }
}

void ml_print_vec2(float vec[2])
{
    for (int i = 0; i < 2; i++) {
        printf("%f ", vec[i]);
    }
    printf("\n");
}

void ml_print_vec3(float vec[3])
{
    for (int i = 0; i < 3; i++) {
        printf("%f ", vec[i]);
    }
    printf("\n");
}

void ml_print_vec4(float vec[4])
{
    for (int i = 0; i < 4; i++) {
        printf("%f ", vec[i]);
    }
    printf("\n");
}

float deg_to_rad(float degrees)
{
    return degrees * M_PI / 180.0;
}
