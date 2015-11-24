
#include "lcd5110.h"

static struct SPI_Master_t spi_master;
static struct LCD5110_t    lcd;

void lcd5110_init(  unsigned char contrast, PORT_t *port, unsigned char dc_pin,
                    unsigned char rst_pin, unsigned char sce_pin)
{
    lcd.port = port;
    lcd.dc_pin = dc_pin;
    lcd.rst_pin = rst_pin;
    lcd.sce_pin = sce_pin;

    spi_init_master(&spi_master, &SPIC, &PORTC, SPI_MODE_0_gc,
                    SPI_PRESCALER_DIV128_gc, false, false);

    lcd.port->DIRSET = lcd.dc_pin | lcd.rst_pin | lcd.sce_pin;

    lcd.port->OUTCLR = lcd.rst_pin;
    lcd.port->OUTSET = lcd.sce_pin;
    _delay_us(1);
    lcd.port->OUTSET = lcd.rst_pin;

    lcd5110_write_byte(LCD5110_EXT_SET,      LCD5110_CMD);
    lcd5110_write_byte(contrast,             LCD5110_CMD);
    lcd5110_write_byte(LCD5110_TEMP_COEF,    LCD5110_CMD);
    lcd5110_write_byte(LCD5110_BIAS,         LCD5110_CMD);

    lcd5110_write_byte(LCD5110_STD_SET,      LCD5110_CMD);
    lcd5110_write_byte(LCD5110_DISP_NORM,    LCD5110_CMD);

    lcd5110_clear();
}

void lcd5110_write_byte(unsigned char data, unsigned char dc)
{
    if (dc == LCD5110_DATA) {
        lcd.port->OUTSET = lcd.dc_pin;
    } else if (dc == LCD5110_CMD) {
        lcd.port->OUTCLR = lcd.dc_pin;
    }

    lcd.port->OUTCLR = lcd.sce_pin;
    spi_write(&spi_master, data);
    lcd.port->OUTSET = lcd.sce_pin;
}

void lcd5110_write_array(unsigned char *array, unsigned short length)
{
    lcd.port->OUTSET = lcd.dc_pin; /* Sending data. */

    lcd.port->OUTCLR = lcd.sce_pin;
    for (int i = 0; i < length; i++) {
        spi_write(&spi_master, array[i]);
    }
    lcd.port->OUTSET = lcd.sce_pin;
}

void lcd5110_clear(void)
{
    for (int i = 0; i < LCD5110_BYTES; i++) {
        lcd5110_write_byte(0x00, LCD5110_DATA);
    }
}

void lcd5110_position(unsigned char x, unsigned char y)
{
    lcd5110_write_byte(LCD5110_X_ADDR | x, LCD5110_CMD);
    lcd5110_write_byte(LCD5110_Y_ADDR | y, LCD5110_CMD);
}
