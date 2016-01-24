// Information ----------------------------------------------------------------

/*	Library:		libXmegaA
 *	Purpose:		Basic graphics functions for use with a single dimensional
 *					array buffer.
 *	Author(s):		Shaun Karran
 *	Created:		November 2015
*/

#pragma once

#include <stdint.h>

#include "fbuf.h"
#include "ml.h"

void gl_frame_buffer(struct FBUF_Buffer_t *buffer);

void gl_vertex_array(float *vertices);

void gl_vertex_index_array(uint16_t *vertex_indices);

void gl_normal_array(float *normals);

void gl_normal_index_array(uint16_t *normal_indices);

void gl_mvmatrix(float mv_matrix[][4]);

void gl_viewport(uint16_t x, uint16_t y, uint16_t width, uint16_t height);

void gl_orthographic(float left, float right, float bottom, float top, float near, float far);

void gl_perspective(float left, float right, float bottom, float top, float near, float far);

void gl_perspective_fov(float fov_y, float aspect_ratio, float near, float far);

// void gl_draw(size_t array_size);

void gl_draw_elements(size_t num_elements);

// static void gl_draw_lines(size_t array_size);

void gl_draw_line(float x1f, float y1f, float x2f, float y2f);

void gl_perspective_devision(float vertex[4], float out[3]);
