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

void gl_orthographic(float left, float right, float bottom, float top, float near, float far);

void gl_perspective(float left, float right, float bottom, float top, float near, float far);

void gl_perspective_fov(float fov_y, float aspect_ratio, float near, float far);

void gl_bind_vertex_array(float vertex_array[]);

void gl_bind_mvmatrix(float mv_matrix[][4]);

void gl_draw(size_t array_size);

static void gl_draw_lines(size_t array_size);

static void gl_draw_line(float x1f, float y1f, float x2f, float y2f);

static void gl_perspective_devision(float vertex[4], float out[3]);

#endif /* _GL_H_ */
