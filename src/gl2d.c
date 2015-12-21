// Information ----------------------------------------------------------------

/*	Library:		libXmegaA
 *	Purpose:		Basic graphics functions for use with a single dimensional
 *					array buffer.
 *	Author(s):		Shaun Karran
 *	Created:		November 2015
*/

// Includes -------------------------------------------------------------------

#include "gl2d.h"

static struct FBUFF_Buffer_t frame_buffer;
static void (*render)(unsigned char *, size_t);

// static vec2_t *VERTEX_ARRAY;
static vec2_t VERTEX_ARRAY[128];
static mat3_t MV_MATRIX;
static mat3_t PROJECTION_MATRIX;
static mat3_t VIEWPORT_MATRIX;

void gl2d_init(size_t width, size_t height, void (*render_function)(unsigned char *, size_t))
{
    fbuff_init(&frame_buffer, width, height);
    render = render_function;

    ml_mat3_identity(&PROJECTION_MATRIX);
    ml_mat3_identity(&VIEWPORT_MATRIX);
    gl2d_viewport(0, 0, width, height);
}

void gl2d_viewport(int x, int y, int width, int height)
{
    width  = width - 1;
    height = height - 1;

    /* Scale from NDC to viewport size, and translate to viewport location. */
    VIEWPORT_MATRIX.values[0][2] = width  / 2.0f + x; /* Move to location of viewport. */
    VIEWPORT_MATRIX.values[1][2] = height / 2.0f + y;
    VIEWPORT_MATRIX.values[0][0] = width  / 2.0f; /* Scale to size of viewport. */
    VIEWPORT_MATRIX.values[1][1] = height / 2.0f;
}

void gl2d_orthographic(float left, float right, float bottom, float top)
{
    /* Transform the viewport to NDC by scaling the viewport to be from -1 to 1 in both axis. */
    PROJECTION_MATRIX.values[0][0] = 2.0f / (right - left); /* Centre on the x axis. */
    PROJECTION_MATRIX.values[1][1] = 2.0f / (top - bottom); /* Centre on the y axis. */

    /* Transform the viewport to clip coords by centring on 0, 0. */
    PROJECTION_MATRIX.values[0][2] = -((float)right + left) / (right - left); /* Centre on the x axis. */
    PROJECTION_MATRIX.values[1][2] = -((float)top + bottom) / (top - bottom); /* Centre on the y axis. */

}

void gl2d_bind_vertex_array(vec2_t *vertex_array, size_t array_length)
{
    // VERTEX_ARRAY = realloc(VERTEX_ARRAY, array_length * sizeof(vec2_t));

    for (size_t i = 0; i < array_length; i++) {
        VERTEX_ARRAY[i] = vertex_array[i];
    }
}

void gl2d_bind_mvmatrix(mat3_t mv_matrix)
{
    MV_MATRIX = mv_matrix;
}

void gl2d_draw(size_t num_verticies)
{
    vec3_t vertex;

    for (size_t i = 0; i < num_verticies; i++) {
        vertex.values[0] = VERTEX_ARRAY[i].values[0];
        vertex.values[1] = VERTEX_ARRAY[i].values[1];
        vertex.values[2] = 1;

        vertex = ml_multiply_mat3_vec3(&MV_MATRIX, &vertex);
        vertex = ml_multiply_mat3_vec3(&PROJECTION_MATRIX, &vertex);
        vertex = ml_multiply_mat3_vec3(&VIEWPORT_MATRIX, &vertex);

        VERTEX_ARRAY[i].values[0] = vertex.values[0];
        VERTEX_ARRAY[i].values[1] = vertex.values[1];
    }

    gl2d_draw_lines(num_verticies);

    render(frame_buffer.buffer, frame_buffer.size);
    fbuff_clear(&frame_buffer);
}

static void gl2d_draw_lines(size_t num_verticies)
{
    for (size_t i = 0; i < num_verticies - 1; i++) {
        gl2d_draw_line(VERTEX_ARRAY[i], VERTEX_ARRAY[i + 1]);
    }
}

static void gl2d_draw_line(vec2_t p1, vec2_t p2)
{
    int x1 = (int) roundf(p1.values[0]);
    int y1 = (int) roundf(p1.values[1]);
    int x2 = (int) roundf(p2.values[0]);
    int y2 = (int) roundf(p2.values[1]);

    int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int error = dx - dy;
	int error2;
	/* Shift x and y in the correct direction based on line direction. */
	char shift_x = (x1 < x2) ? 1 : -1;
	char shift_y = (y1 < y2) ? 1 : -1;

	while (1) {
		fbuff_set_pixel(x1, y1, &frame_buffer);

		if ((x1 == x2) && (y1 == y2)) {
			break;
		}

		/* Shift the x and/or y position based on accumulated error. */
		error2 = 2 * error;

		if (error2 > -dy) {
			error -= dy;
			x1 += shift_x;
		}
		if (error2 < dx) {
			error += dx;
			y1 += shift_y;
		}
	}
}
