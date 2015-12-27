
#include <stdio.h>
#include <time.h>

#include "ml.h"

#define M 3
#define N 3

void test_1();
void test_2();
void test_3();
void test_4();

int main(void)
{
    // test_1();
    test_2();
    // test_3();

    return 0;
}

void test_1()
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
}

void test_2()
{
    vec3_t vertex;
    mat3_t mv_matrix;
    mat3_t proj_matrix;

    vertex.values[0] = 42;
    vertex.values[1] = 24;
    vertex.values[2] = 1;

    ml_mat3_identity(&mv_matrix);
    ml_mat3_identity(&proj_matrix);
    ml_print_mat3(&mv_matrix);
    ml_print_mat3(&proj_matrix);
    proj_matrix.values[0][2] = -42;
    proj_matrix.values[1][2] = -24;

    vertex = ml_multiply_mat3_vec3(&mv_matrix, &vertex);
    vertex = ml_multiply_mat3_vec3(&proj_matrix, &vertex);

    ml_print_vec3(&vertex);
}

void test_3()
{
    int loops = 10000000;
    clock_t start, end;
    mat2_t mat_a;
    mat2_t mat_b;
    mat2_t result;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            mat_a.values[i][j] = i * 2 + j + 1;
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            mat_b.values[i][j] = 4 - (i * 2 + j);
        }
    }
    ml_print_mat2(&mat_a); printf("\n");
    ml_print_mat2(&mat_b); printf("\n");

    start = clock();
    for (int i = 0; i < loops; i++) {
        result = ml_multiply_mat2_mat2(&mat_a, &mat_b);
    }
    end = clock();
    ml_print_mat2(&result);
    printf("Normal took %f seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);
}
