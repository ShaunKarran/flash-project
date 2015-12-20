
#include "st7565r.h"

static struct ST7565R_t LCD;

void st7565r_init(USART_t *usart, gpio_pin_t chip_select, gpio_pin_t a0, gpio_pin_t reset)
{
    LCD.usart       = usart;
    LCD.chip_select = chip_select;
    LCD.a0          = a0;
    LCD.reset       = reset;

    gpio_set_pin(LCD.chip_select);
    gpio_set_pin(LCD.reset);

    usart_spi_init(usart);

    st7564r_hard_reset();

    st7565r_write_command(ST7565R_CMD_ADC_NORMAL);
    st7565r_write_command(ST7565R_CMD_DISPLAY_NORMAL);
    st7565r_write_command(ST7565R_CMD_REVERSE_SCAN_DIRECTION);
    st7565r_write_command(ST7565R_CMD_LCD_BIAS_1_DIV_6_DUTY33);
    st7565r_write_command(ST7565R_CMD_POWER_CTRL_ALL_ON);
    st7565r_write_command(ST7565R_CMD_BOOSTER_RATIO_SET);
    st7565r_write_command(ST7565R_CMD_BOOSTER_RATIO_2X_3X_4X);
    st7565r_write_command(ST7565R_CMD_VOLTAGE_RESISTOR_RATIO_1);
    st7565r_write_command(ST7565R_CMD_DISPLAY_ON);
}

void st7565r_write_data(unsigned char data)
{
    gpio_set_pin(LCD.a0);

    gpio_clr_pin(LCD.chip_select);
    usart_spi_write(LCD.usart, data);
    gpio_set_pin(LCD.chip_select);
}

void st7565r_write_command(unsigned char cmd)
{
    gpio_clr_pin(LCD.a0);

    gpio_clr_pin(LCD.chip_select);
    usart_spi_write(LCD.usart, cmd);
    gpio_set_pin(LCD.chip_select);
}

void st7565r_write_array(unsigned char *array, size_t length)
{
    unsigned char page = 0;

    for (page = 0; page < ST7565R_HEIGHT / 8; page++) {
        st7565r_write_page(page, array + page * ST7565R_WIDTH);
    }
}

void st7565r_clear(void)
{
}

void st7565r_position(unsigned char x, unsigned char y)
{
}

void st7564r_hard_reset(void)
{
    gpio_clr_pin(LCD.a0);
    gpio_clr_pin(LCD.reset);
    _delay_us(5);
    gpio_set_pin(LCD.reset);
    _delay_us(5);
}

void st7565r_set_page(unsigned char page)
{
    /* Make sure that the address is 4 bits (only 8 pages). */
    page &= 0x0F;
    st7565r_write_command(ST7565R_CMD_PAGE_SET(page));
}

void st7565r_set_column(unsigned char column)
{
    /* Make sure the address is 7 bits. */
	column &= 0x7F;
	st7565r_write_command(ST7565R_CMD_COLUMN_SET_MSB(column >> 4));
	st7565r_write_command(ST7565R_CMD_COLUMN_SET_LSB(column & 0x0F));
}

void st7565r_write_page(unsigned char page, unsigned char *data)
{
    st7565r_set_page(page);
    st7565r_set_column(0);

    for (size_t i = 0; i < ST7565R_WIDTH; i++) {
        st7565r_write_data(data[i]);
    }
}
