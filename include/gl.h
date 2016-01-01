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

// void gl_perspective(float fov_y, float aspect_ratio, float near, float far);
void gl_perspective(float left, float right, float bottom, float top, float near, float far);

void gl_bind_vertex_array(vec3_t *vertex_array);

void gl_bind_mvmatrix(mat4_t *mv_matrix);

void gl_draw(size_t num_verticies);

static void gl_draw_lines(size_t num_verticies);

static void gl_draw_line(float x1f, float y1f, float x2f, float y2f);

static vec3_t gl_perspective_devision(vec4_t *vertex);

#endif /* _GL_H_ */
