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
#include "fbuff.h"
#include "ml.h"

void gl2d_init(size_t width, size_t height, void (*render_function)(unsigned char *, size_t));

void gl2d_viewport(int x, int y, int width, int height);

void gl2d_orthographic(float left, float right, float bottom, float top);

void gl2d_bind_vertex_array(vec2_t *vertex_array, size_t array_length);

void gl2d_bind_mvmatrix(mat3_t *mv_matrix);

void gl2d_draw(size_t num_verticies);

static void gl2d_draw_lines(size_t num_verticies);

static void gl2d_draw_line(vec2_t p1, vec2_t p2);

#endif /* _GL2D_H_ */