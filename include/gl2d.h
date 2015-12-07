// Information ----------------------------------------------------------------

/*	Library:		libXmegaA
 *	Purpose:		Basic graphics functions for use with a single dimensional
 *					array buffer.
 *	Author(s):		Shaun Karran
 *	Created:		November 2015
*/

#ifndef _GL2D_H_
#define _GL2D_H_

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "bitwise.h"

struct GL2D_t {
    size_t width;
    size_t height;
    size_t length;
    unsigned char *frame_buffer;
    void (*render)(unsigned char *, unsigned short);
};

typedef struct Vec3_t {
    float x;
    float y;
    float z;
} vec3_t;

typedef float mat3_t[3][3];

void gl2d_init( size_t width, size_t height,
                void (*render)(unsigned char *, unsigned short));

void gl2d_bind_vertex_array(float *vertex_array, size_t array_length);

void gl2d_set_mvmatrix(mat3_t *mv_matrix);

void gl2d_draw(size_t num_verticies);

void gl2d_clear_buffer();

static void gl2d_vertex_shader(size_t num_verticies);

static void gl2d_fill_faces();

static void gl2d_draw_lines(size_t num_verticies);

static void gl2d_draw_line(float x1, float y1, float x2, float y2);

static void gl2d_draw_pixel(int x, int y);

/* Matrix functions. */
void gl2d_mat3_identity(mat3_t a);

vec3_t gl2d_multiply_mat3_vec3(mat3_t matrix, vec3_t vector);

#endif /* _GL2D_H_ */
