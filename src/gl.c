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
static void (*render)(uint8_t *, size_t);

static float    *VERT_ARRAY;           /* Points to users array of vertices. */
static uint16_t *VERT_INDEX_ARRAY;
static float    *NORM_ARRAY;
static uint16_t *NORM_INDEX_ARRAY;
static float    (*MV_MATRIX)[4];    /* Model-View matrix. To transform to eye coordinates. */
static float    P_MATRIX[4][4];     /* Projection matrix. To transform to clip coordinates. */
static float    V_MATRIX[3][3];     /* View matrix. To transform to screen coordinates. */

void gl_init(uint16_t width, uint16_t height, void (*render_function)(unsigned char *, size_t))
{
    fbuff_init(&frame_buffer, width, height);
    render = render_function;

    gl_viewport(0, 0, width, height);
}

void gl_viewport(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    ml_mat3_identity(V_MATRIX);

    width  = width - 1;
    height = height - 1;
    V_MATRIX[0][2] = width  / 2.0f + x; /* Move to location of viewport. */
    V_MATRIX[1][2] = height / 2.0f + y;
    V_MATRIX[0][0] = width  / 2.0f; /* Scale to size of viewport. */
    V_MATRIX[1][1] = height / 2.0f;
}

void gl_orthographic(float left, float right, float bottom, float top, float near, float far)
{
    ml_mat4_identity(P_MATRIX);

    P_MATRIX[0][0] =  2.0f / (right - left);
    P_MATRIX[1][1] =  2.0f / (top - bottom);
    P_MATRIX[2][2] = -2.0f / (far - near);
    P_MATRIX[0][3] = -(right + left) / (right - left);
    P_MATRIX[1][3] = -(top + bottom) / (top - bottom);
    P_MATRIX[2][3] = -(far + near) / (far - near);
}

void gl_perspective(float left, float right, float bottom, float top, float near, float far)
{
    ml_mat4_identity(P_MATRIX);

    P_MATRIX[0][0] = 2 * near / (right - left);
    P_MATRIX[1][1] = 2 * near / (top - bottom);
    P_MATRIX[2][2] = -(far + near) / (far - near);
    P_MATRIX[0][2] = (right + left) / (right - left);
    P_MATRIX[1][2] = (top + bottom) / (top - bottom);
    P_MATRIX[2][3] = -(2 * far * near) / (far - near);
    P_MATRIX[3][2] = -1;
}

void gl_perspective_fov(float fov_y, float aspect_ratio, float near, float far)
{
    ml_mat4_identity(P_MATRIX);

    float f = 1 / tan(fov_y / 2);
    P_MATRIX[0][0] = f / aspect_ratio;
    P_MATRIX[1][1] = f;
    P_MATRIX[2][2] = (far + near) / (near - far);
    P_MATRIX[2][3] = (2 * far * near) / (near - far);
    P_MATRIX[3][2] = -1;
}

void gl_bind_vert_array(float array[])
{
    VERT_ARRAY = array;
}

void gl_bind_vert_index_array(uint16_t array[])
{
    VERT_INDEX_ARRAY = array;
}

void gl_bind_norm_array(float array[])
{
    NORM_ARRAY = array;
}

void gl_bind_norm_index_array(uint16_t array[])
{
    NORM_INDEX_ARRAY = array;
}

void gl_bind_mvmatrix(float mv_matrix[][4])
{
    MV_MATRIX = mv_matrix;
}

// void gl_draw(size_t array_size)
// {
//     float  vertex4[4];
//     float  vertex3[3];
//
//     TEMP_VERTICES = (float *)realloc(TEMP_VERTICES, array_size * sizeof(float));
//
//     for (size_t i = 0; i < array_size - 2; i += 3) {
//         vertex4[0] = VERT_ARRAY[i];
//         vertex4[1] = VERT_ARRAY[i + 1];
//         vertex4[2] = VERT_ARRAY[i + 2];
//         vertex4[3] = 1;
//
//         ml_multiply_mat4_vec4(MV_MATRIX, vertex4, vertex4);
//         // printf("Before projection:"); ml_print_vec4(vertex4);
//         // printf("P_MATRIX\n"); ml_print_mat4(P_MATRIX);
//         ml_multiply_mat4_vec4(P_MATRIX, vertex4, vertex4);
//         gl_perspective_devision(vertex4, vertex3);
//         // printf("After projection:"); ml_print_vec3(vertex3);
//         vertex3[2] = 1;
//         ml_multiply_mat3_vec3(V_MATRIX, vertex3, vertex3);
//         // printf("Screen coords:"); ml_print_vec3(vertex3);
//         // sleep(1);
//
//         TEMP_VERTICES[i]     = vertex3[0];
//         TEMP_VERTICES[i + 1] = vertex3[1];
//         TEMP_VERTICES[i + 2] = vertex3[2];
//     }
//
//     gl_draw_lines(array_size);
//
//     render(frame_buffer.buffer, frame_buffer.size);
//     fbuff_clear(&frame_buffer);
// }

void gl_draw_elements(size_t num_elements)
{
    float  vertex4_a[4];
    float  vertex4_b[4];
    float  vertex4_c[4];
    float  vertex3_a[3];
    float  vertex3_b[3];
    float  vertex3_c[3];
    size_t index;

    for (size_t i = 0; i < num_elements - 1; i += 3) { // Draw 1 face per loop.
        index = (VERT_INDEX_ARRAY[i] - 1) * 3; // OBJs use 1-indexing.
        vertex4_a[0] = VERT_ARRAY[index];
        vertex4_a[1] = VERT_ARRAY[index + 1];
        vertex4_a[2] = VERT_ARRAY[index + 2];
        vertex4_a[3] = 1;

        index = (VERT_INDEX_ARRAY[i + 1] - 1) * 3; // OBJs use 1-indexing.
        vertex4_b[0] = VERT_ARRAY[index];
        vertex4_b[1] = VERT_ARRAY[index + 1];
        vertex4_b[2] = VERT_ARRAY[index + 2];
        vertex4_b[3] = 1;

        index = (VERT_INDEX_ARRAY[i + 2] - 1) * 3; // OBJs use 1-indexing.
        vertex4_c[0] = VERT_ARRAY[index];
        vertex4_c[1] = VERT_ARRAY[index + 1];
        vertex4_c[2] = VERT_ARRAY[index + 2];
        vertex4_c[3] = 1;

        ml_multiply_mat4_vec4(MV_MATRIX, vertex4_a, vertex4_a);
        ml_multiply_mat4_vec4(MV_MATRIX, vertex4_b, vertex4_b);
        ml_multiply_mat4_vec4(MV_MATRIX, vertex4_c, vertex4_c);
        ml_multiply_mat4_vec4(P_MATRIX, vertex4_a, vertex4_a);
        ml_multiply_mat4_vec4(P_MATRIX, vertex4_b, vertex4_b);
        ml_multiply_mat4_vec4(P_MATRIX, vertex4_c, vertex4_c);
        gl_perspective_devision(vertex4_a, vertex3_a);
        gl_perspective_devision(vertex4_b, vertex3_b);
        gl_perspective_devision(vertex4_c, vertex3_c);
        vertex3_a[2] = 1; // Temp fix.
        vertex3_b[2] = 1;
        vertex3_c[2] = 1;
        ml_multiply_mat3_vec3(V_MATRIX, vertex3_a, vertex3_a);
        ml_multiply_mat3_vec3(V_MATRIX, vertex3_b, vertex3_b);
        ml_multiply_mat3_vec3(V_MATRIX, vertex3_c, vertex3_c);

        gl_draw_line(vertex3_a[0], vertex3_a[1], vertex3_b[0], vertex3_b[1]);
        gl_draw_line(vertex3_b[0], vertex3_b[1], vertex3_c[0], vertex3_c[1]);
        gl_draw_line(vertex3_a[0], vertex3_a[1], vertex3_c[0], vertex3_c[1]);
    }

    render(frame_buffer.data, frame_buffer.size);
    fbuff_clear(&frame_buffer);
}

// static void gl_draw_lines(size_t array_size)
// {
//     for (size_t i = 0; i < array_size - 5; i += 3) {
//         gl_draw_line(TEMP_VERTICES[i],
//                      TEMP_VERTICES[i + 1],
//                      TEMP_VERTICES[i + 3],
//                      TEMP_VERTICES[i + 4]);
//     }
// }

void gl_draw_line(float x1f, float y1f, float x2f, float y2f)
{
    int16_t x1 = (int16_t)roundf(x1f);
    int16_t y1 = (int16_t)roundf(y1f);
    int16_t x2 = (int16_t)roundf(x2f);
    int16_t y2 = (int16_t)roundf(y2f);

    int16_t dx = abs(x2 - x1);
	int16_t dy = abs(y2 - y1);
	int16_t error = dx - dy;
	int16_t error2;
	/* Shift x and y in the correct direction based on line direction. */
	int8_t shift_x = (x1 < x2) ? 1 : -1;
	int8_t shift_y = (y1 < y2) ? 1 : -1;

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

void gl_perspective_devision(float vertex[4], float out[3])
{
    out[0] = vertex[0] / vertex[3];
    out[1] = vertex[1] / vertex[3];
    out[2] = vertex[2] / vertex[3];
}
