// Information ----------------------------------------------------------------

/*	Library:		libXmegaA
 *	Purpose:		Basic graphics functions for use with a single dimensional
 *					array buffer.
 *	Author(s):		Shaun Karran
 *	Created:		November 2015
*/

// Includes -------------------------------------------------------------------

#include "gfx.h"

static struct FBUF_Buffer_t *FRAME_BUFFER;

// Function Definitions -------------------------------------------------------
void gfx_bind_buffer(struct FBUF_Buffer_t *buffer)
{
	FRAME_BUFFER = buffer;
}

struct GFX_Sprite_t gfx_create_sprite(uint8_t *bitmap, uint16_t width, uint16_t height)
{
	struct GFX_Sprite_t sprite;

	sprite.width = width;
	sprite.height = height;
	sprite.bitmap = bitmap;

	return sprite;
}

void gfx_draw_line(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
	int8_t dx = abs(x2 - x1);
	int8_t dy = abs(y2 - y1);
	int8_t error = dx - dy;
	int8_t error2;
	/* Shift x and y in the correct direction based on line direction. */
	int8_t shift_x = (x1 < x2) ? 1 : -1;
	int8_t shift_y = (y1 < y2) ? 1 : -1;

	for (;;) {
		fbuf_set_pixel(x1, y1, FRAME_BUFFER);

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

void gfx_draw_circle(int16_t x, int16_t y, uint16_t radius)
{
	int16_t x_dist = radius;
	int16_t y_dist = 0;
	int16_t error = 1 - x_dist; /* Used to determine if the 'slow direction' should increment. */

	while (x_dist >= y_dist) {
		/* Algorithm only draws a single octant. Each line draws a differnt octant.
		 * Draws the left and right 'sides' of the circle. */
		fbuf_set_pixel(x + x_dist, y + y_dist, FRAME_BUFFER);
		fbuf_set_pixel(x - x_dist, y + y_dist, FRAME_BUFFER);
		fbuf_set_pixel(x + x_dist, y - y_dist, FRAME_BUFFER);
		fbuf_set_pixel(x - x_dist, y - y_dist, FRAME_BUFFER);

		/* Draws the top and bottom of the circle. */
		fbuf_set_pixel(x + y_dist, y + x_dist, FRAME_BUFFER);
		fbuf_set_pixel(x - y_dist, y + x_dist, FRAME_BUFFER);
		fbuf_set_pixel(x + y_dist, y - x_dist, FRAME_BUFFER);
		fbuf_set_pixel(x - y_dist, y - x_dist, FRAME_BUFFER);

		/* Increment y ('fast direction') and determine if x should be incremented. */
		y_dist++;
		if (error > 0) {
			x_dist--;
			error += 2 * (y_dist - x_dist + 1);
		} else {
			error += 2 * y_dist + 1;
		}
	}
}

void gfx_draw_char(char character, const uint8_t font[][FONT_CHAR_WIDTH], int16_t x, int16_t y)
{
	for (int i = 0; i < FONT_CHAR_WIDTH; i++) {
		for (int j = 0; j < FONT_CHAR_HEIGHT; j++) {
			// if (get_bit(pgm_read_byte(&font[character - FONT_OFFSET][i]), j)) {
			if (get_bit(font[character - FONT_OFFSET][i], j)) {
				fbuf_set_pixel(x + i, y + j, FRAME_BUFFER);
			}
		}
	}
}

void gfx_draw_string(char* str, const uint8_t font[][FONT_CHAR_WIDTH], int16_t x, int16_t y)
{
	int i = 0;

	while (str[i] != '\0')
	{
		gfx_draw_char(str[i], font, x + (i * (FONT_CHAR_WIDTH + FONT_SPACE)), y);
		i++;
	}
}

void gfx_draw_sprite(struct GFX_Sprite_t *sprite, int16_t x, int16_t y)
{
	int16_t index;
	uint8_t bit;

	for (int i = 0; i < sprite->width; i++) {
		for (int j = 0; j < sprite->height; j++) {
			index = ((j / 8) * sprite->width) + i;
			bit = j % 8;

			if (get_bit(sprite->bitmap[index], bit)) {
				fbuf_set_pixel(x + i, y + j, FRAME_BUFFER);
			}
		}
	}
}
