// Information ----------------------------------------------------------------

/*	Library:		libXmegaA
 *	Purpose:		Basic graphics functions for use with a single dimensional
 *					array buffer.
 *	Author(s):		Shaun Karran
 *	Created:		November 2015
*/

#pragma once

// #include <avr/pgmspace.h>
#include <stdlib.h> /* abs() */

#include "ascii_font.h"
#include "bitwise.h"
#include "fbuf.h"

struct GFX_Sprite_t {
	unsigned char width;
	unsigned char height;
	unsigned char *bitmap;
};

// Function Prototypes --------------------------------------------------------
void gfx_bind_buffer(struct FBUF_Buffer_t *buffer);

struct GFX_Sprite_t gfx_create_sprite(uint8_t *bitmap, uint16_t width, uint16_t height);

void gfx_draw_line(int16_t x1, int16_t y1, int16_t x2, int16_t y2);

void gfx_draw_circle(int16_t x, int16_t y, uint16_t radius);

void gfx_draw_char(char character, const uint8_t font[][FONT_CHAR_WIDTH], int16_t x, int16_t y);

void gfx_draw_string(char* str, const uint8_t font[][FONT_CHAR_WIDTH], int16_t x, int16_t y);

void gfx_draw_sprite(struct GFX_Sprite_t *sprite, int16_t x, int16_t y);
