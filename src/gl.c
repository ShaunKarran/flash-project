// Information ----------------------------------------------------------------

/*	Library:		libXmegaA
 *	Purpose:		Basic graphics functions for use with a single dimensional
 *					array buffer.
 *	Author(s):		Shaun Karran
 *	Created:		November 2015
*/

// Includes -------------------------------------------------------------------

#include "gl.h"

#include <unistd.h> /* For sleep() for testing. */

static struct FBUFF_Buffer_t frame_buffer;
static void (*render)(unsigned char *, size_t);

static vec3_t *VERTEX_ARRAY;    /* Points to users array of vertices. */
static vec3_t *TEMP_VERTICES;   /* To store transformed vertices while drawing. */
static mat4_t *MV_MATRIX;       /* Model-View matrix. To transform to eye coordinates. */
static mat4_t P_MATRIX;         /* Projection matrix. To transform to clip coordinates. */
static mat3_t VIEW_MATRIX;      /* To transform to screen coordinates. */

void gl_init(size_t width, size_t height, void (*render_function)(unsigned char *, size_t))
{
    fbuff_init(&frame_buffer, width, height);
    render = render_function;

    gl_viewport(0, 0, width, height);
}

void gl_viewport(int x, int y, int width, int height)
{
    width  = width - 1;
    height = height - 1;
    ml_mat3_identity(&VIEW_MATRIX);

    /* Scale from NDC to viewport size, and translate to viewport location. */
    VIEW_MATRIX.values[0][2] = width  / 2.0f + x; /* Move to location of viewport. */
    VIEW_MATRIX.values[1][2] = height / 2.0f + y;
    VIEW_MATRIX.values[0][0] = width  / 2.0f; /* Scale to size of viewport. */
    VIEW_MATRIX.values[1][1] = height / 2.0f;
}

void gl_orthographic(float left, float right, float bottom, float top, float near, float far)
{
    ml_mat4_identity(&P_MATRIX);

    /* Transform viewport to clip coords by centring on 0, 0. */
    P_MATRIX.values[0][0] =  2.0f / (right - left);
    P_MATRIX.values[1][1] =  2.0f / (top - bottom);
    P_MATRIX.values[2][2] = -2.0f / (far - near);
    P_MATRIX.values[0][3] = -(right + left) / (right - left);
    P_MATRIX.values[1][3] = -(top + bottom) / (top - bottom);
    P_MATRIX.values[2][3] = -(far + near) / (far - near);

    /* NOTE: Simplified version from http://www.songho.ca/opengl/gl_projectionmatrix.html */
    // P_MATRIX.values[0][0] =  1.0f / right;
    // P_MATRIX.values[1][1] =  1.0f / top;
    // P_MATRIX.values[2][2] = -2.0f / (far - near);
    // P_MATRIX.values[2][3] = -(far + near) / (far - near);

}

// void gl_perspective(float fov_y, float aspect_ratio, float near, float far)
// {
//     float f;
//
//     fov_y = fov_y * M_PI / 180.0; /* Convert from degrees to radians. */
//     f = 1 / tan(fov_y / 2);
//     ml_mat4_identity(&P_MATRIX);
//
//     P_MATRIX.values[0][0] = f / aspect_ratio;
//     P_MATRIX.values[1][1] = f;
//     P_MATRIX.values[2][2] = (near + far) / (near - far);
//     P_MATRIX.values[2][3] = (2 * near * far) / (near - far);
//     P_MATRIX.values[3][2] = -1;
// }

void gl_perspective(float left, float right, float bottom, float top, float near, float far)
{
    ml_mat4_identity(&P_MATRIX);

    P_MATRIX.values[0][0] = near / right;
    P_MATRIX.values[1][1] = near / top;
    P_MATRIX.values[2][2] = -(far + near) / (far - near);
    P_MATRIX.values[2][3] = (-2 * far * near) / (far - near);
    P_MATRIX.values[3][2] = -1;
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
    vec4_t vertex4;
    vec3_t vertex3;

    TEMP_VERTICES = realloc(TEMP_VERTICES, num_verticies * sizeof(vec3_t));

    for (size_t i = 0; i < num_verticies; i++) {
        vertex4.values[0] = VERTEX_ARRAY[i].values[0];
        vertex4.values[1] = VERTEX_ARRAY[i].values[1];
        vertex4.values[2] = VERTEX_ARRAY[i].values[2];
        vertex4.values[3] = 1;

        vertex4 = ml_multiply_mat4_vec4(MV_MATRIX, &vertex4);
        // printf("Before projection:"); ml_print_vec4(&vertex4);
        // printf("P_MATRIX\n"); ml_print_mat4(&P_MATRIX);
        vertex4 = ml_multiply_mat4_vec4(&P_MATRIX, &vertex4);
        vertex3 = gl_perspective_devision(&vertex4);
        // printf("After projection:"); ml_print_vec3(&vertex3);
        vertex3.values[2] = 1;
        vertex3 = ml_multiply_mat3_vec3(&VIEW_MATRIX, &vertex3);
        // printf("Screen coords:"); ml_print_vec3(&vertex3);
        // sleep(2);

        TEMP_VERTICES[i] = vertex3;
    }

    gl_draw_lines(num_verticies);

    render(frame_buffer.buffer, frame_buffer.size);
    fbuff_clear(&frame_buffer);
}

static void gl_draw_lines(size_t num_verticies)
{
    size_t i_1;
    for (size_t i = 0; i < num_verticies - 1; i++) {
        i_1 = i + 1; /* Hopefully gain efficiency by only calcuating once. */
        gl_draw_line(TEMP_VERTICES[i].values[0],
                     TEMP_VERTICES[i].values[1],
                     TEMP_VERTICES[i_1].values[0],
                     TEMP_VERTICES[i_1].values[1]);
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

static vec3_t gl_perspective_devision(vec4_t *vertex)
{
    vec3_t result;

    result.values[0] = vertex->values[0] / vertex->values[3];
    result.values[1] = vertex->values[1] / vertex->values[3];
    result.values[2] = vertex->values[2] / vertex->values[3];

    return result;
}
