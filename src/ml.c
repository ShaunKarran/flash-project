
#include "ml.h"

void ml_mat2_identity(float mat[4])
{
    memset(mat, 0, 4 * sizeof(float));
    mat[0] = 1;
    mat[3] = 1;
}

void ml_mat3_identity(float mat[9])
{
    memset(mat, 0, 9 * sizeof(float));
    mat[0] = 1;
    mat[4] = 1;
    mat[8] = 1;
}

void ml_mat4_identity(float mat[16])
{
    memset(mat, 0, 16 * sizeof(float));
    mat[0] = 1;
    mat[5] = 1;
    mat[10] = 1;
    mat[15] = 1;
}

void ml_multiply_mat2_mat2(float mat_a[4], float mat_b[4], float out[4])
{
    float temp[4];

    temp[0] = mat_a[0] * mat_b[0] + mat_a[1] * mat_b[2];
    temp[1] = mat_a[0] * mat_b[1] + mat_a[1] * mat_b[3];
    temp[2] = mat_a[2] * mat_b[0] + mat_a[3] * mat_b[2];
    temp[3] = mat_a[2] * mat_b[1] + mat_a[3] * mat_b[3];

    out[0] = temp[0];
    out[1] = temp[1];
    out[2] = temp[2];
    out[3] = temp[3];
}

void ml_multiply_mat3_mat3(float mat_a[9], float mat_b[9], float out[9])
{
    float temp[9];

    temp[0] = mat_a[0] * mat_b[0] + mat_a[1] * mat_b[3] + mat_a[2] * mat_b[6];
    temp[1] = mat_a[0] * mat_b[1] + mat_a[1] * mat_b[4] + mat_a[2] * mat_b[7];
    temp[2] = mat_a[0] * mat_b[2] + mat_a[1] * mat_b[5] + mat_a[2] * mat_b[8];
    temp[3] = mat_a[3] * mat_b[0] + mat_a[4] * mat_b[3] + mat_a[5] * mat_b[6];
    temp[4] = mat_a[3] * mat_b[1] + mat_a[4] * mat_b[4] + mat_a[5] * mat_b[7];
    temp[5] = mat_a[3] * mat_b[2] + mat_a[4] * mat_b[5] + mat_a[5] * mat_b[8];
    temp[6] = mat_a[6] * mat_b[0] + mat_a[7] * mat_b[3] + mat_a[8] * mat_b[6];
    temp[7] = mat_a[6] * mat_b[1] + mat_a[7] * mat_b[4] + mat_a[8] * mat_b[7];
    temp[8] = mat_a[6] * mat_b[2] + mat_a[7] * mat_b[5] + mat_a[8] * mat_b[8];

    out[0] = temp[0];
    out[1] = temp[1];
    out[2] = temp[2];
    out[3] = temp[3];
    out[4] = temp[4];
    out[5] = temp[5];
    out[6] = temp[6];
    out[7] = temp[7];
    out[8] = temp[8];
}

void ml_multiply_mat4_mat4(float mat_a[16], float mat_b[16], float out[16])
{
    float temp[16];

    temp[0] = mat_a[0] * mat_b[0] + mat_a[1] * mat_b[4] + mat_a[2] * mat_b[8] + mat_a[3] * mat_b[12];
    temp[1] = mat_a[0] * mat_b[1] + mat_a[1] * mat_b[5] + mat_a[2] * mat_b[9] + mat_a[3] * mat_b[13];
    temp[2] = mat_a[0] * mat_b[2] + mat_a[1] * mat_b[6] + mat_a[2] * mat_b[10] + mat_a[3] * mat_b[14];
    temp[3] = mat_a[0] * mat_b[3] + mat_a[1] * mat_b[7] + mat_a[2] * mat_b[11] + mat_a[3] * mat_b[15];
    temp[4] = mat_a[4] * mat_b[0] + mat_a[5] * mat_b[4] + mat_a[6] * mat_b[8] + mat_a[7] * mat_b[12];
    temp[5] = mat_a[4] * mat_b[1] + mat_a[5] * mat_b[5] + mat_a[6] * mat_b[9] + mat_a[7] * mat_b[13];
    temp[6] = mat_a[4] * mat_b[2] + mat_a[5] * mat_b[6] + mat_a[6] * mat_b[10] + mat_a[7] * mat_b[14];
    temp[7] = mat_a[4] * mat_b[3] + mat_a[5] * mat_b[7] + mat_a[6] * mat_b[11] + mat_a[7] * mat_b[15];
    temp[8] = mat_a[8] * mat_b[0] + mat_a[9] * mat_b[4] + mat_a[10] * mat_b[8] + mat_a[11] * mat_b[12];
    temp[9] = mat_a[8] * mat_b[1] + mat_a[9] * mat_b[5] + mat_a[10] * mat_b[9] + mat_a[11] * mat_b[13];
    temp[10] = mat_a[8] * mat_b[2] + mat_a[9] * mat_b[6] + mat_a[10] * mat_b[10] + mat_a[11] * mat_b[14];
    temp[11] = mat_a[8] * mat_b[3] + mat_a[9] * mat_b[7] + mat_a[10] * mat_b[11] + mat_a[11] * mat_b[15];
    temp[12] = mat_a[12] * mat_b[0] + mat_a[13] * mat_b[4] + mat_a[14] * mat_b[8] + mat_a[15] * mat_b[12];
    temp[13] = mat_a[12] * mat_b[1] + mat_a[13] * mat_b[5] + mat_a[14] * mat_b[9] + mat_a[15] * mat_b[13];
    temp[14] = mat_a[12] * mat_b[2] + mat_a[13] * mat_b[6] + mat_a[14] * mat_b[10] + mat_a[15] * mat_b[14];
    temp[15] = mat_a[12] * mat_b[3] + mat_a[13] * mat_b[7] + mat_a[14] * mat_b[11] + mat_a[15] * mat_b[15];

    out[0] = temp[0];
    out[1] = temp[1];
    out[2] = temp[2];
    out[3] = temp[3];
    out[4] = temp[4];
    out[5] = temp[5];
    out[6] = temp[6];
    out[7] = temp[7];
    out[8] = temp[8];
    out[9] = temp[9];
    out[10] = temp[10];
    out[11] = temp[11];
    out[12] = temp[12];
    out[13] = temp[13];
    out[14] = temp[14];
    out[15] = temp[15];
}

void ml_multiply_mat3_vec3(float mat[9], float vec[3], float out[3])
{
    float temp[3];

    temp[0] = mat[0] * vec[0] + mat[1] * vec[1] + mat[2] * vec[2];
    temp[1] = mat[3] * vec[0] + mat[4] * vec[1] + mat[5] * vec[2];
    temp[2] = mat[6] * vec[0] + mat[6] * vec[1] + mat[7] * vec[2];

    out[0] = temp[0];
    out[1] = temp[1];
    out[2] = temp[2];
}

void ml_multiply_mat4_vec4(float mat[16], float vec[4], float out[4])
{
    float temp[4];

    temp[0] = mat[0] * vec[0] + mat[1] * vec[1] + mat[2] * vec[2] + mat[3] * vec[3];
    temp[1] = mat[4] * vec[0] + mat[5] * vec[1] + mat[6] * vec[2] + mat[7] * vec[3];
    temp[2] = mat[8] * vec[0] + mat[9] * vec[1] + mat[10] * vec[2] + mat[11] * vec[3];
    temp[3] = mat[12] * vec[0] + mat[13] * vec[1] + mat[14] * vec[2] + mat[15] * vec[3];

    out[0] = temp[0];
    out[1] = temp[1];
    out[2] = temp[2];
    out[3] = temp[3];
}

void ml_translate(float mat[16], float x, float y, float z)
{
    mat[3] += x;
    mat[7] += y;
    mat[11] += z;
}

void ml_rotate_x(float mat[16], float angle)
{
    float rotation[16];
    float c, s;

    ml_mat4_identity(rotation);
    c = cos(deg_to_rad(angle));
    s = sin(deg_to_rad(angle));
    rotation[5] =  c;
    rotation[6] = -s;
    rotation[9] =  s;
    rotation[10] =  c;

    ml_multiply_mat4_mat4(rotation, mat, mat);
}

void ml_rotate_y(float mat[16], float angle)
{
    float rotation[16];
    float c, s;

    ml_mat4_identity(rotation);
    c = cos(deg_to_rad(angle));
    s = sin(deg_to_rad(angle));
    rotation[0] =  c;
    rotation[2] =  s;
    rotation[8] = -s;
    rotation[10] =  c;

    ml_multiply_mat4_mat4(rotation, mat, mat);
}

void ml_rotate_z(float mat[16], float angle)
{
    float rotation[16];
    float c, s;

    ml_mat4_identity(rotation);
    c = cos(deg_to_rad(angle));
    s = sin(deg_to_rad(angle));
    rotation[0] =  c;
    rotation[1] =  s;
    rotation[4] = -s;
    rotation[5] =  c;

    ml_multiply_mat4_mat4(rotation, mat, mat);
}

void ml_print_mat2(float mat[4])
{
    for (int m = 0; m < 2; m++) {
        for (int n = 0; n < 2; n++) {
            printf("%f ", mat[m * 2 + n]);
        }
        printf("\n");
    }
}

void ml_print_mat3(float mat[9])
{
    for (int m = 0; m < 3; m++) {
        for (int n = 0; n < 3; n++) {
            printf("%f ", mat[m * 3 + n]);
        }
        printf("\n");
    }
}

void ml_print_mat4(float mat[16])
{
    for (int m = 0; m < 4; m++) {
        for (int n = 0; n < 4; n++) {
            printf("%f ", mat[m * 4 + n]);
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
