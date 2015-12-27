// Information ----------------------------------------------------------------

/*	Library:		libXmegaA
 *	Purpose:		Basic graphics functions for use with a single dimensional
 *					array buffer.
 *	Author(s):		Shaun Karran
 *	Created:		November 2015
*/

// Includes -------------------------------------------------------------------

#include "gl.h"

static struct FBUFF_Buffer_t frame_buffer;
static void (*render)(unsigned char *, size_t);

static vec3_t *VERTEX_ARRAY;
static vec3_t *TRANSFORMED_VERTICES;
static mat4_t *MV_MATRIX;
static mat4_t PROJECTION_MATRIX;
static mat4_t VIEWPORT_MATRIX;

void gl_init(size_t width, size_t height, void (*render_function)(unsigned char *, size_t))
{
    fbuff_init(&frame_buffer, width, height);
    render = render_function;

    ml_mat4_identity(&PROJECTION_MATRIX);
    ml_mat4_identity(&VIEWPORT_MATRIX);
    gl_viewport(0, 0, width, height);
}

void gl_viewport(int x, int y, int width, int height)
{
    width  = width - 1;
    height = height - 1;

    /* Scale from NDC to viewport size, and translate to viewport location. */
    VIEWPORT_MATRIX.values[0][3] = width  / 2.0f + x; /* Move to location of viewport. */
    VIEWPORT_MATRIX.values[1][3] = height / 2.0f + y;
    VIEWPORT_MATRIX.values[0][0] = width  / 2.0f; /* Scale to size of viewport. */
    VIEWPORT_MATRIX.values[1][1] = height / 2.0f;
}

void gl_orthographic(float left, float right, float bottom, float top, float near, float far)
{
    /* NOTE: Can be simplified. See http://www.songho.ca/opengl/gl_projectionmatrix.html */
    /* Transform viewport to clip coords by centring on 0, 0. */
    PROJECTION_MATRIX.values[0][0] = 2.0f / (right - left);
    PROJECTION_MATRIX.values[1][1] = 2.0f / (top - bottom);
    PROJECTION_MATRIX.values[2][2] = 2.0f / (far - near);

    /* Transform viewport to NDC by scaling the viewport to be from -1 to 1 in both axis. */
    PROJECTION_MATRIX.values[0][3] = -((float)right + left) / (right - left);
    PROJECTION_MATRIX.values[1][3] = -((float)top + bottom) / (top - bottom);
    PROJECTION_MATRIX.values[2][3] = -((float)far + near) / (far - near);
}

void gl_bind_vertex_array(vec3_t *vertex_array)
{
    VERTEX_ARRAY = vertex_array;
}

void gl_bind_mvmatrix(mat4_t *mv_matrix)
{
    MV_MATRIX = mv_matrix;
}

void gl_draw(size_t num_verticies)
{
    vec4_t vertex;
    TRANSFORMED_VERTICES = realloc(TRANSFORMED_VERTICES, num_verticies * sizeof(vec3_t));

    for (size_t i = 0; i < num_verticies; i++) {
        vertex.values[0] = VERTEX_ARRAY[i].values[0];
        vertex.values[1] = VERTEX_ARRAY[i].values[1];
        vertex.values[2] = VERTEX_ARRAY[i].values[2];
        vertex.values[3] = 1;

        vertex = ml_multiply_mat4_vec4(MV_MATRIX, &vertex);
        vertex = ml_multiply_mat4_vec4(&PROJECTION_MATRIX, &vertex);
        vertex = ml_multiply_mat4_vec4(&VIEWPORT_MATRIX, &vertex);

        TRANSFORMED_VERTICES[i].values[0] = vertex.values[0];
        TRANSFORMED_VERTICES[i].values[1] = vertex.values[1];
        TRANSFORMED_VERTICES[i].values[2] = vertex.values[2];
    }

    gl_draw_lines(num_verticies);

    render(frame_buffer.buffer, frame_buffer.size);
    fbuff_clear(&frame_buffer);
}

static void gl_draw_lines(size_t num_verticies)
{
    for (size_t i = 0; i < num_verticies - 1; i++) {
        gl_draw_line(TRANSFORMED_VERTICES[i].values[0],
                     TRANSFORMED_VERTICES[i].values[1],
                     TRANSFORMED_VERTICES[i + 1].values[0],
                     TRANSFORMED_VERTICES[i + 1].values[1]);
    }
}

/* NOTE: These should be vec2_t. This is a temporary solution. */
static void gl_draw_line(float x1f, float y1f, float x2f, float y2f)
{
    int x1 = (int)roundf(x1f);
    int y1 = (int)roundf(y1f);
    int x2 = (int)roundf(x2f);
    int y2 = (int)roundf(y2f);

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
