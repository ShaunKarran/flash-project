
#pragma once

#include <math.h>
#include <stdio.h>
#include <string.h>

void ml_mat2_identity(float mat[][2]);
void ml_mat3_identity(float mat[][3]);
void ml_mat4_identity(float mat[][4]);

void ml_multiply_mat2_mat2(float a[][2], float b[][2], float out[][2]);
void ml_multiply_mat3_mat3(float a[][3], float b[][3], float out[][3]);
void ml_multiply_mat4_mat4(float a[][4], float b[][4], float out[][4]);

void ml_multiply_mat3_vec3(float mat[][3], float vec[3], float out[3]);
void ml_multiply_mat4_vec4(float mat[][4], float vec[4], float out[4]);

void ml_translate(float mat[][4], float x, float y, float z);
void ml_rotate_x(float mat[][4], float angle);
void ml_rotate_y(float mat[][4], float angle);
void ml_rotate_z(float mat[][4], float angle);

void ml_print_mat2(float mat[][2]);
void ml_print_mat3(float mat[][3]);
void ml_print_mat4(float mat[][4]);

void ml_print_vec2(float vec[2]);
void ml_print_vec3(float vec[3]);
void ml_print_vec4(float vec[4]);

float deg_to_rad(float degrees);
