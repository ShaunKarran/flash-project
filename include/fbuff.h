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

struct FBUFF_Buffer_t {
    uint16_t width;
    uint16_t height;
    size_t size;
    uint8_t *buffer;
};

bool fbuff_init(struct FBUFF_Buffer_t *frame_buffer, uint16_t width, uint16_t height);

void fbuff_clear(struct FBUFF_Buffer_t *frame_buffer);

void fbuff_fill(struct FBUFF_Buffer_t *frame_buffer);

bool fbuff_set_pixel(uint16_t x, uint16_t y, struct FBUFF_Buffer_t *frame_buffer);

bool fbuff_clr_pixel(uint16_t x, uint16_t y, struct FBUFF_Buffer_t *frame_buffer);

// void fbuff_fill_faces(struct FBUFF_Buffer_t *frame_buffer);
