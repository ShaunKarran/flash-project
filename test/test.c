
#include <stdio.h>
#include <time.h>

#include "ml.h"

#define M 3
#define N 3

void test_identity();
void test_multiply_mat2_mat2();
void test_multiply_mat4_vec4();

int main(void)
{
    test_identity();
    test_multiply_mat2_mat2();
    test_multiply_mat4_vec4();

    return 0;
}

void test_identity()
{
    float mat2[2][2];
    float mat3[3][3];
    float mat4[4][4];

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            mat2[i][j] = i * 2 + j + 1;
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat3[i][j] = i * 3 + j + 1;
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mat4[i][j] = i * 4 + j + 1;
        }
    }
    printf("Before identity.\n");
    ml_print_mat2(mat2); printf("\n");
    ml_print_mat3(mat3); printf("\n");
    ml_print_mat4(mat4); printf("\n");

    ml_mat2_identity(mat2);
    ml_mat3_identity(mat3);
    ml_mat4_identity(mat4);

    printf("After identity.\n");
    ml_print_mat2(mat2); printf("\n");
    ml_print_mat3(mat3); printf("\n");
    ml_print_mat4(mat4); printf("\n");
}

void test_multiply_mat2_mat2()
{
    float mat_a[2][2] = {{1, 2}, {3, 4}};
    float mat_b[2][2] = {{4, 3}, {2, 1}};

    ml_multiply_mat2_mat2(mat_a, mat_b, mat_a);

    printf("mat2 * mat2 test.\n");
    ml_print_mat2(mat_a); printf("\n");
}

void test_multiply_mat4_vec4()
{
    float matrix[4][4];
    float vertex[4] = {20, 0, 0, 1};
    
    ml_mat4_identity(matrix);
    ml_rotate_y(matrix, 5);

    printf("matrix:\n");
    ml_print_mat4(matrix); printf("\n");

    ml_multiply_mat4_vec4(matrix, vertex, vertex);

    printf("vector:\n");
    ml_print_vec4(vertex);
}
