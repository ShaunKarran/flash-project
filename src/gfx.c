// Information ----------------------------------------------------------------

/*	Library:		libXmegaA
 *	Purpose:		Basic graphics functions for use with a single dimensional
 *					array buffer.
 *	Author(s):		Shaun Karran
 *	Created:		November 2015
*/

// Includes -------------------------------------------------------------------

#include "gfx.h"

static struct GFX_Buffer_t *GFX;

// Function Definitions -------------------------------------------------------
bool gfx_init(struct GFX_Buffer_t *gfx, unsigned short width, unsigned short height,
			  void (*render)(unsigned char *, unsigned short))
{
	gfx->width = width;
	gfx->height = height;
	gfx->length = width * height / 8;

	gfx->buffer = calloc(gfx->length, sizeof(char));
	if (gfx->buffer == NULL) {
		return false;
	}

	gfx->render = render;

	return true;
}

void gfx_bind_buffer(struct GFX_Buffer_t *gfx)
{
	GFX = gfx;
}

void gfx_render()
{
	GFX->render(GFX->buffer, GFX->length);
}

void gfx_clear()
{
    for (int i = 0; i < GFX->length; i++) {
        GFX->buffer[i] = 0x00;
    }
}

void gfx_draw_line(short x1, short y1, short x2, short y2)
{
	char dx = abs(x2 - x1);
	char dy = abs(y2 - y1);
	char error = dx - dy;
	char error2;
	/* Shift x and y in the correct direction based on line direction. */
	char shift_x = (x1 < x2) ? 1 : -1;
	char shift_y = (y1 < y2) ? 1 : -1;

	while (1) {
		gfx_draw_pixel(x1, y1);

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

void gfx_draw_circle(short x, short y, unsigned char radius)
{
	char x_dist, y_dist, error;

	x_dist = radius;
	y_dist = 0;
	error = 1 - x_dist; // Used to determine if the 'slow direction' should increment.

	while (x_dist >= y_dist) {
		// Algorithm only draws a single octant. Each line draws a differnt octant.
		// Draws the left and right 'sides' of the circle.
		gfx_draw_pixel(x + x_dist, y + y_dist);
		gfx_draw_pixel(x - x_dist, y + y_dist);
		gfx_draw_pixel(x + x_dist, y - y_dist);
		gfx_draw_pixel(x - x_dist, y - y_dist);

		// Draws the top and bottom of the circle.
		gfx_draw_pixel(x + y_dist, y + x_dist);
		gfx_draw_pixel(x - y_dist, y + x_dist);
		gfx_draw_pixel(x + y_dist, y - x_dist);
		gfx_draw_pixel(x - y_dist, y - x_dist);

		// Increment y ('fast direction') and determine if x should be incremented.
		y_dist++;
		if (error > 0) {
			x_dist--;
			error += 2 * (y_dist - x_dist + 1);
		} else {
			error += 2 * y_dist + 1;
		}
	}
}

void gfx_draw_char( char character, const char font[][FONT_CHAR_WIDTH],
					short x, short y)
{
	for (int i = 0; i < FONT_CHAR_WIDTH; i++) {
		for (int j = 0; j < FONT_CHAR_HEIGHT; j++) {
			if (get_bit(pgm_read_byte(&font[character - FONT_OFFSET][i]), j)) {
				gfx_draw_pixel(x + i, y + j);
			}
		}
	}
}

void gfx_draw_string(	char* str, const char font[][FONT_CHAR_WIDTH],
						short x, short y)
{
	int i = 0;

	while (str[i] != '\0')
	{
		gfx_draw_char(str[i], font, x + (i * (FONT_CHAR_WIDTH + FONT_SPACE)), y);
		i++;
	}
}

void gfx_draw_sprite(struct GFX_Sprite_t *sprite, short x, short y)
{
	short byte;
	unsigned char bit;

	for (int i = 0; i < sprite->width; i++) {
		for (int j = 0; j < sprite->height; j++) {
			byte = ((j / 8) * sprite->width) + i;
			bit = j % 8;

			if (get_bit(sprite->bitmap[byte], bit)) {
				gfx_draw_pixel(x + i, y + j);
			}
		}
	}
}

void gfx_init_sprite(	struct GFX_Sprite_t *sprite, unsigned char *bitmap,
						unsigned short width, unsigned short height)
{
	sprite->width = width;
	sprite->height = height;
	sprite->bitmap = bitmap;
}

bool gfx_draw_pixel(short x, short y)
{
	short byte = gfx_buffer_position(x, y);

	if (byte >= 0) {
		unsigned char bit = y % 8;
		set_bit(GFX->buffer[byte], bit);
		return true;
	}

	return false;
}

bool gfx_clr_pixel(short x, short y)
{
	short byte = gfx_buffer_position(x, y);

	if (byte >= 0) {
		unsigned char bit = y % 8;
		clr_bit(GFX->buffer[byte], bit);
		return true;
	}

	return false;
}

char gfx_get_pixel(short x, short y)
{
	short byte = gfx_buffer_position(x, y);

	if (byte >= 0) {
		unsigned char bit = y % 8;
		return get_bit(GFX->buffer[byte], bit);
	}

	return -1;
}

static short gfx_buffer_position(short x, short y)
{
	if (x < 0 || x >= GFX->width || y < 0 || y >= GFX->height) {
		return -1;
	}
	/* y / 8 finds row, then * row size moves to start of that row. */
	return ((y / 8) * GFX->width) + x;
}
