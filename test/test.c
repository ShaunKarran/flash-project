
#include <stdio.h>
#include <time.h>

#include "ml.h"

#define M 3
#define N 3

void test_identity();
void test_multiply_mat4_vec4();

int main(void)
{
    test_identity();
    test_multiply_mat4_vec4();

    return 0;
}

void test_identity()
{
    mat2_t mat2;
    mat3_t mat3;
    mat4_t mat4;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            mat2.values[i][j] = i * 2 + j + 1;
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat3.values[i][j] = i * 3 + j + 1;
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mat4.values[i][j] = i * 4 + j + 1;
        }
    }
    printf("Before identity.\n");
    ml_print_mat2(&mat2); printf("\n");
    ml_print_mat3(&mat3); printf("\n");
    ml_print_mat4(&mat4); printf("\n");

    ml_mat2_identity(&mat2);
    ml_mat3_identity(&mat3);
    ml_mat4_identity(&mat4);

    printf("After identity.\n");
    ml_print_mat2(&mat2); printf("\n");
    ml_print_mat3(&mat3); printf("\n");
    ml_print_mat4(&mat4); printf("\n");
}

void test_multiply_mat4_vec4()
{
    mat4_t matrix;
    vec4_t vertex;

    vertex.values[0] = 20;
    vertex.values[1] =  0;
    vertex.values[2] =  0;
    vertex.values[3] =  1;

    ml_mat4_identity(&matrix);
    ml_rotate_y(&matrix, 5);

    printf("matrix:\n");
    ml_print_mat4(&matrix); printf("\n");

    vertex = ml_multiply_mat4_vec4(&matrix, &vertex);

    printf("vector:\n");
    ml_print_vec4(&vertex);
}
