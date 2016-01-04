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

static float *VERTEX_ARRAY;      /* Points to users array of vertices. */
static float *TEMP_VERTICES;     /* To store transformed vertices while drawing. */
static float MV_MATRIX[4][4];    /* Model-View matrix. To transform to eye coordinates. */
static float P_MATRIX[4][4];     /* Projection matrix. To transform to clip coordinates. */
static float V_MATRIX[3][3];     /* View matrix. To transform to screen coordinates. */

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
    ml_mat3_identity(V_MATRIX);

    /* Scale from NDC to viewport size, and translate to viewport location. */
    V_MATRIX[0][2] = width  / 2.0f + x; /* Move to location of viewport. */
    V_MATRIX[1][2] = height / 2.0f + y;
    V_MATRIX[0][0] = width  / 2.0f; /* Scale to size of viewport. */
    V_MATRIX[1][1] = height / 2.0f;
}

void gl_orthographic(float left, float right, float bottom, float top, float near, float far)
{
    ml_mat4_identity(P_MATRIX);

    /* Transform viewport to clip coords by centring on 0, 0. */
    P_MATRIX[0][0] =  2.0f / (right - left);
    P_MATRIX[1][1] =  2.0f / (top - bottom);
    P_MATRIX[2][2] = -2.0f / (far - near);
    P_MATRIX[0][3] = -(right + left) / (right - left);
    P_MATRIX[1][3] = -(top + bottom) / (top - bottom);
    P_MATRIX[2][3] = -(far + near) / (far - near);

    /* NOTE: Simplified version from http://www.songho.ca/opengl/gl_projectionmatrix.html */
    // P_MATRIX[0][0] =  1.0f / right;
    // P_MATRIX[1][1] =  1.0f / top;
    // P_MATRIX[2][2] = -2.0f / (far - near);
    // P_MATRIX[2][3] = -(far + near) / (far - near);

}

void gl_perspective(float left, float right, float bottom, float top, float near, float far)
{
    ml_mat4_identity(P_MATRIX);

    P_MATRIX[0][0] = near / right;
    P_MATRIX[1][1] = near / top;
    P_MATRIX[2][2] = -(far + near) / (far - near);
    P_MATRIX[2][3] = -(2 * far * near) / (far - near);
    P_MATRIX[3][2] = -1;
}

void gl_perspective_fov(float fov_y, float aspect_ratio, float near, float far)
{
    float f;

    fov_y = fov_y * M_PI / 180.0; /* Convert from degrees to radians. */
    f = 1 / tan(fov_y / 2);
    ml_mat4_identity(P_MATRIX);

    P_MATRIX[0][0] = f / aspect_ratio;
    P_MATRIX[1][1] = f;
    P_MATRIX[2][2] = -(far + near) / (far - near);
    P_MATRIX[2][3] = -(2 * far * near) / (far - near);
    P_MATRIX[3][2] = -1;
}

void gl_bind_vertex_array(float vertex_array[])
{
    VERTEX_ARRAY = vertex_array;
}

void gl_bind_mvmatrix(float mv_matrix[][4])
{
    for (int m = 0; m < 4; m++) {
        for (int n = 0; n < 4; n++) {
            MV_MATRIX[m][n] = mv_matrix[m][n];
        }
    }
}

void gl_draw(size_t array_size)
{
    float  vertex4[4];
    float  vertex3[3];

    TEMP_VERTICES = (float *)realloc(TEMP_VERTICES, array_size * sizeof(float));

    for (size_t i = 0; i < array_size - 2; i += 3) {
        vertex4[0] = VERTEX_ARRAY[i];
        vertex4[1] = VERTEX_ARRAY[i + 1];
        vertex4[2] = VERTEX_ARRAY[i + 2];
        vertex4[3] = 1;

        ml_multiply_mat4_vec4(MV_MATRIX, vertex4, vertex4);
        // printf("Before projection:"); ml_print_vec4(vertex4);
        // printf("P_MATRIX\n"); ml_print_mat4(P_MATRIX);
        ml_multiply_mat4_vec4(P_MATRIX, vertex4, vertex4);
        gl_perspective_devision(vertex4, vertex3);
        // printf("After projection:"); ml_print_vec3(vertex3);
        vertex3[2] = 1;
        ml_multiply_mat3_vec3(V_MATRIX, vertex3, vertex3);
        // printf("Screen coords:"); ml_print_vec3(vertex3);
        // sleep(1);

        TEMP_VERTICES[i]     = vertex3[0];
        TEMP_VERTICES[i + 1] = vertex3[1];
        TEMP_VERTICES[i + 2] = vertex3[2];
    }

    gl_draw_lines(array_size);

    render(frame_buffer.buffer, frame_buffer.size);
    fbuff_clear(&frame_buffer);
}

static void gl_draw_lines(size_t array_size)
{
    for (size_t i = 0; i < array_size - 5; i += 3) {
        gl_draw_line(TEMP_VERTICES[i],
                     TEMP_VERTICES[i + 1],
                     TEMP_VERTICES[i + 3],
                     TEMP_VERTICES[i + 4]);
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

static void gl_perspective_devision(float vertex[4], float out[3])
{
    out[0] = vertex[0] / vertex[3];
    out[1] = vertex[1] / vertex[3];
    out[2] = vertex[2] / vertex[3];
}
