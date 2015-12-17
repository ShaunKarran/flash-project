// Information ----------------------------------------------------------------

/*	Library:		libXmegaA
 *	Purpose:		Basic graphics functions for use with a single dimensional
 *					array buffer.
 *	Author(s):		Shaun Karran
 *	Created:		November 2015
*/

// Includes -------------------------------------------------------------------

#include "fbuff.h"

void fbuff_init(struct FBUFF_Buffer_t *frame_buffer, size_t width, size_t height)
{
    frame_buffer->width  = width;
    frame_buffer->height = height;
    frame_buffer->size = width * height / 8;

    frame_buffer->buffer = calloc(frame_buffer->size, sizeof(unsigned char));
}

void fbuff_clear(struct FBUFF_Buffer_t *frame_buffer)
{
    memset(frame_buffer->buffer, 0x00, frame_buffer->size);
}

void fbuff_fill(struct FBUFF_Buffer_t *frame_buffer)
{
    memset(frame_buffer->buffer, 0xFF, frame_buffer->size);
}

void fbuff_set_pixel(int x, int y, struct FBUFF_Buffer_t *frame_buffer)
{
    /* Position is outside of the buffer. */
    if (x < 0 || x >= frame_buffer->width ||
        y < 0 || y >= frame_buffer->height) {
        return;
    }

    size_t byte = y / 8 * frame_buffer->width + x;
    char bit = y % 8;

    set_bit(frame_buffer->buffer[byte], bit);
}

void fbuff_clr_pixel(int x, int y, struct FBUFF_Buffer_t *frame_buffer)
{
    /* Position is outside of the buffer. */
    if (x < 0 || x >= frame_buffer->width ||
        y < 0 || y >= frame_buffer->height) {
        return;
    }

    size_t byte = y / 8 * frame_buffer->width + x;
    char bit = y % 8;

    clr_bit(frame_buffer->buffer[byte], bit);
}

void fbuff_fill_faces(struct FBUFF_Buffer_t *frame_buffer)
{
    size_t buffer_position;
    bool previous_pixel = false;
    bool this_pixel     = false;
    bool inside         = false;

    for (size_t y = 0; y < frame_buffer->height; y++) {
        inside = false;

        for (size_t x = 0; x < frame_buffer->width; x++) {
            buffer_position = y / 8 * frame_buffer->width + x;

            previous_pixel = this_pixel;
            this_pixel = get_bit(frame_buffer->buffer[buffer_position], y % 8);

            if (previous_pixel && !this_pixel) {
                inside = !inside;
            } else if (previous_pixel && this_pixel) { /* Horizontal edge. */
                inside = true;
            }

            if (inside) {
                set_bit(frame_buffer->buffer[buffer_position], y % 8);
            }
        }
    }
}
