// Information ----------------------------------------------------------------

/*	Library:		libXmegaA
 *	Purpose:		Basic graphics functions for use with a single dimensional
 *					array buffer.
 *	Author(s):		Shaun Karran
 *	Created:		November 2015
*/

#ifndef _GL_H_
#define _GL_H_

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "bitwise.h"
#include "fbuff.h"
#include "ml.h"

void gl_init(size_t width, size_t height, void (*render_function)(unsigned char *, size_t));

void gl_viewport(int x, int y, int width, int height);

void gl_orthographic(float left, float right, float bottom, float top);

void gl_bind_vertex_array(vec2_t *vertex_array);

void gl_bind_mvmatrix(mat3_t *mv_matrix);

void gl_draw(size_t num_verticies);

static void gl_draw_lines(size_t num_verticies);

static void gl_draw_line(vec2_t p1, vec2_t p2);

#endif /* _GL_H_ */
