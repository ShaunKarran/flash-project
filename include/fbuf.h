// Information ----------------------------------------------------------------

/*	Library:		libXmegaA
 *	Purpose:		Black & white frame buffer to store frame information from graphics libraries
 *                  and draw to the screen.
 *	Author(s):		Shaun Karran
 *	Created:		November 2015
*/

#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "bitwise.h"

struct FBUF_Buffer_t {
    uint16_t width;
    uint16_t height;
    size_t   size;
    uint8_t  *data;
};

bool fbuf_init(struct FBUF_Buffer_t *frame_buffer, uint16_t width, uint16_t height);

void fbuf_clear(struct FBUF_Buffer_t *frame_buffer);

void fbuf_fill(struct FBUF_Buffer_t *frame_buffer);

bool fbuf_set_pixel(uint16_t x, uint16_t y, struct FBUF_Buffer_t *frame_buffer);

bool fbuf_clr_pixel(uint16_t x, uint16_t y, struct FBUF_Buffer_t *frame_buffer);

// void fbuff_fill_faces(struct FBUFF_Buffer_t *frame_buffer);
