
#ifndef _LCD5110_H_
#define _LCD5110_H_

#include <util/delay.h>

#include "spi.h"

/* Display pixel dimensions. */
#define LCD5110_WIDTH  84
#define LCD5110_HEIGHT 48
#define LCD5110_PIXELS LCD5110_WIDTH * LCD5110_HEIGHT
#define LCD5110_BYTES  LCD5110_PIXELS / 8

/* LCD instruction modes. */
#define LCD5110_EXT_SET         0x21
#define LCD5110_STD_SET         0x20
/* Standard instructions. */
#define LCD5110_DISP_NORM       0x0C
#define LCD5110_X_ADDR          0x40
#define LCD5110_Y_ADDR          0x80
/* Extended instructions. */
#define LCD5110_TEMP_COEF       0x04
#define LCD5110_BIAS            0x13
#define LCD5110_CONTRAST_LOW    0xAF
#define LCD5110_CONTRAST_MID    0xBF
#define LCD5110_CONTRAST_HIGH   0xCF

struct LCD5110_t {
    PORT_t        *port;
    unsigned char dc_pin;
    unsigned char rst_pin;
    unsigned char sce_pin;
};

void lcd5110_init(  unsigned char contrast, PORT_t *port, unsigned char dc_pin,
                    unsigned char rst_pin, unsigned char sce_pin);

void lcd5110_write_data(unsigned char data);

void lcd5110_write_command(unsigned char cmd);

void lcd5110_write_array(unsigned char *array, unsigned short length);

void lcd5110_clear(void);

void lcd5110_position(unsigned char x, unsigned char y);

#endif /* _LCD5110_H_ */
