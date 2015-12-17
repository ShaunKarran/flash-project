// Information ----------------------------------------------------------------

/*	Library:		libXmegaA
 *	Purpose:		Black & white frame buffer to store frame information from graphics libraries
 *                  and draw to the screen.
 *	Author(s):		Shaun Karran
 *	Created:		November 2015
*/

#ifndef _FBUFF_H_
#define _FBUFF_H_

#include <stdlib.h>
#include <string.h>

#include "bitwise.h"

struct FBUFF_Buffer_t {
    size_t width;
    size_t height;
    size_t size;
    unsigned char *buffer;
};

void fbuff_init(struct FBUFF_Buffer_t *frame_buffer, size_t width, size_t height);

void fbuff_clear(struct FBUFF_Buffer_t *frame_buffer);

void fbuff_fill(struct FBUFF_Buffer_t *frame_buffer);

void fbuff_set_pixel(int x, int y, struct FBUFF_Buffer_t *frame_buffer);

void fbuff_clr_pixel(int x, int y, struct FBUFF_Buffer_t *frame_buffer);

#endif /* _FBUFF_H_ */
