// Information ----------------------------------------------------------------

/*	Library:		libXmegaA
 *	Purpose:		Basic graphics functions for use with a single dimensional
 *					array buffer.
 *	Author(s):		Shaun Karran
 *	Created:		November 2015
*/

// Includes -------------------------------------------------------------------

#include "gl2d.h"

static struct GL2D_t gl2d;

static float  *VERTEX_ARRAY;
static mat3_t *MV_MATRIX;

void gl2d_init( size_t width, size_t height,
                void (*render)(unsigned char *, unsigned short))
{
    gl2d.width  = width;
    gl2d.height = height;
    gl2d.length = width * height / 8;
    gl2d.render = render;

    gl2d.frame_buffer = calloc(gl2d.length, sizeof(unsigned char));
}

void gl2d_bind_vertex_array(float *vertex_array, size_t array_length)
{
    VERTEX_ARRAY = realloc(VERTEX_ARRAY, array_length);

    for (int i = 0; i < array_length; i++) {
        VERTEX_ARRAY[i] = vertex_array[i];
    }
}

void gl2d_set_mvmatrix(mat3_t *mv_matrix)
{
    MV_MATRIX = mv_matrix;
}

void gl2d_draw(size_t num_verticies)
{
    gl2d_vertex_shader(num_verticies);
    // gl2d_projection(num_verticies);
    // gl2d_normalise_coords();
    // gl2d_clipper();
    // gl2d_window_coords();
    gl2d_draw_lines(num_verticies);
    // gl2d_fill_faces();

    gl2d.render(gl2d.frame_buffer, gl2d.length);
}

void gl2d_clear_buffer()
{
    for (int i = 0; i < gl2d.length; i++) {
        gl2d.frame_buffer[i] = 0x00;
    }
}

static void gl2d_vertex_shader(size_t num_verticies)
{
    vec3_t vertex;

    for (int i = 0; i < num_verticies * 2; i += 2) {
        vertex.x = VERTEX_ARRAY[i];
        vertex.y = VERTEX_ARRAY[i + 1];
        vertex.z = 1;

        vertex = gl2d_multiply_mat3_vec3(*MV_MATRIX, vertex);

        VERTEX_ARRAY[i] = vertex.x;
        VERTEX_ARRAY[i + 1] = vertex.y;
    }
}

static void gl2d_fill_faces()
{
    int buffer_position;
    bool previous_pixel = false;
    bool this_pixel     = false;
    bool inside         = false;

    for (int y = 0; y < gl2d.height; y++) {
        inside = false;

        for (int x = 0; x < gl2d.width; x++) {
            buffer_position = y / 8 * gl2d.width + x;

            previous_pixel = this_pixel;
            this_pixel = get_bit(gl2d.frame_buffer[buffer_position], y % 8);

            if (previous_pixel && !this_pixel) {
                inside = !inside;
            } else if (previous_pixel && this_pixel) { /* Horizontal edge. */
                inside = true;
            }

            if (inside) {
                set_bit(gl2d.frame_buffer[buffer_position], y % 8);
            }
        }
    }
}

static void gl2d_draw_lines(size_t num_verticies)
{
    for (int i = 0; i < num_verticies * 2 - 2; i += 2) {
        gl2d_draw_line( VERTEX_ARRAY[i], VERTEX_ARRAY[i + 1],
                        VERTEX_ARRAY[i + 2], VERTEX_ARRAY[i + 3]);
    }
}

static void gl2d_draw_line(float x1f, float y1f, float x2f, float y2f)
{
    int x1 = (int) roundf(x1f);
    int y1 = (int) roundf(y1f);
    int x2 = (int) roundf(x2f);
    int y2 = (int) roundf(y2f);

    int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int error = dx - dy;
	int error2;
	/* Shift x and y in the correct direction based on line direction. */
	char shift_x = (x1 < x2) ? 1 : -1;
	char shift_y = (y1 < y2) ? 1 : -1;

	while (1) {
		gl2d_draw_pixel(x1, y1);

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

static void gl2d_draw_pixel(int x, int y)
{
    int buffer_position = y / 8 * gl2d.width + x;

    if (buffer_position > -1 && buffer_position < gl2d.length) {
        unsigned char bit = y % 8;
        set_bit(gl2d.frame_buffer[buffer_position], bit);
    }
}

void gl2d_mat3_identity(mat3_t a)
{
    for (int m = 0; m < 3; m++) {
        for (int n = 0; n < 3; n++) {
            if (m == n) {
                a[m][n] = 1;
            } else {
                a[m][n] = 0;
            }
        }
    }
}

vec3_t gl2d_multiply_mat3_vec3(mat3_t matrix, vec3_t vector)
{
    vec3_t temp;

    temp.x = matrix[0][0] * vector.x + matrix[0][1] * vector.y + matrix[0][2] * vector.z;
    temp.y = matrix[1][0] * vector.x + matrix[1][1] * vector.y + matrix[1][2] * vector.z;
    temp.z = matrix[2][0] * vector.x + matrix[2][1] * vector.y + matrix[2][2] * vector.z;

    return temp;
}
