// Information ----------------------------------------------------------------

/*	Library:		libXmegaA
 *	Purpose:		Basic graphics functions for use with a single dimensional
 *					array buffer.
 *	Author(s):		Shaun Karran
 *	Created:		November 2015
*/

#ifndef _GFX_H_
#define _GFX_H_

#include <avr/pgmspace.h>
#include <stdbool.h>
#include <stdlib.h> /* abs, calloc */

#include "ascii_font.h"
#include "bitwise.h"

struct GFX_Buffer_t {
	unsigned short width;
	unsigned short height;
    unsigned int   length;
	unsigned char  *buffer;
	void (*render)(unsigned char *, size_t);
};

struct GFX_Sprite_t {
	unsigned char width;
	unsigned char height;
	unsigned char *bitmap;
};

// Function Prototypes --------------------------------------------------------
bool gfx_init(struct GFX_Buffer_t *gfx, unsigned short width, unsigned short height,
			  void (*render)(unsigned char *, size_t));

void gfx_bind_buffer(struct GFX_Buffer_t *gfx);

void gfx_render();

void gfx_clear();

void gfx_draw_line(short x1, short y1, short x2, short y2);

void gfx_draw_circle(short x, short y, unsigned char radius);

void gfx_draw_char(	char character, const char font[][FONT_CHAR_WIDTH],
					short x, short y);

void gfx_draw_string(	char* str, const char font[][FONT_CHAR_WIDTH],
						short x, short y);

void gfx_draw_sprite(	struct GFX_Sprite_t *sprite,
						short x, short y);

void gfx_init_sprite(	struct GFX_Sprite_t *sprite, unsigned char *bitmap,
						unsigned short width, unsigned short height);

bool gfx_draw_pixel(short x, short y);

bool gfx_clr_pixel(short x, short y);

char gfx_get_pixel(short x, short y);

static short gfx_buffer_position(short x, short y);

#endif // _GFX_H_
