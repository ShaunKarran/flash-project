
#include "st7565r.h"

static struct USART_SPI_t usart;
static struct ST7565R_t   lcd;

void st7565r_init(void)
{
    // lcd.data_port  = &PORTD;
    // lcd.clk_port   = &PORTD;
    lcd.a0_port    = &PORTD;
    lcd.cs_port    = &PORTF;
    lcd.rst_port   = &PORTA;
    lcd.bl_port    = &PORTE;

    // lcd.data_pin   = PIN3_bm;
    // lcd.clk_pin    = PIN1_bm;
    lcd.a0_pin     = PIN0_bm;
    lcd.cs_pin     = PIN3_bm;
    lcd.rst_pin    = PIN3_bm;
    lcd.bl_pin     = PIN4_bm;

    usart_spi_init(&usart, &USARTD0, &PORTD);

    // lcd.data_port->DIRSET   = lcd.data_pin;
    // lcd.clk_port->DIRSET   = lcd.clk_pin;
    lcd.a0_port->DIRSET   = lcd.a0_pin;
    lcd.cs_port->DIRSET   = lcd.cs_pin;
    lcd.rst_port->DIRSET  = lcd.rst_pin;
    lcd.bl_port->DIRSET   = lcd.bl_pin;

    // lcd.data_port->OUTSET = lcd.data_pin;
    // lcd.clk_port->OUTSET = lcd.clk_pin;
    lcd.cs_port->OUTSET  = lcd.cs_pin;
    lcd.a0_port->OUTCLR  = lcd.a0_pin;
    lcd.rst_port->OUTCLR = lcd.rst_pin;
    _delay_us(5);
    lcd.rst_port->OUTSET = lcd.rst_pin;
    _delay_us(5);

    lcd.bl_port->OUTSET = lcd.bl_pin;

    lcd.cs_port->OUTCLR = lcd.cs_pin;
    st7565r_write_command(ST7565R_CMD_ADC_NORMAL);
    st7565r_write_command(ST7565R_CMD_DISPLAY_NORMAL);
    st7565r_write_command(ST7565R_CMD_REVERSE_SCAN_DIRECTION);
    st7565r_write_command(ST7565R_CMD_LCD_BIAS_1_DIV_6_DUTY33);
    st7565r_write_command(ST7565R_CMD_POWER_CTRL_ALL_ON);
    st7565r_write_command(ST7565R_CMD_BOOSTER_RATIO_SET);
    st7565r_write_command(ST7565R_CMD_BOOSTER_RATIO_2X_3X_4X);
    st7565r_write_command(ST7565R_CMD_VOLTAGE_RESISTOR_RATIO_1);
    st7565r_write_command(ST7565R_CMD_DISPLAY_ON);
    lcd.cs_port->OUTSET = lcd.cs_pin;
}

void st7565r_write_data(unsigned char data)
{
    lcd.a0_port->OUTSET = lcd.a0_pin;

    // for (int i = 7; i >= 0; i--) {
    //     lcd.clk_port->OUTCLR = lcd.clk_pin;
    //     if (get_bit(data, i)) {
    //         lcd.data_port->OUTSET = lcd.data_pin;
    //     } else {
    //         lcd.data_port->OUTCLR = lcd.data_pin;
    //     }
    //     lcd.clk_port->OUTSET = lcd.clk_pin;
    // }
    usart_spi_write(&usart, data);
}

void st7565r_write_command(unsigned char cmd)
{
    lcd.a0_port->OUTCLR = lcd.a0_pin;

    // for (int i = 7; i >= 0; i--) {
    //     lcd.clk_port->OUTCLR = lcd.clk_pin;
    //     if (get_bit(cmd, i)) {
    //         lcd.data_port->OUTSET = lcd.data_pin;
    //     } else {
    //         lcd.data_port->OUTCLR = lcd.data_pin;
    //     }
    //     lcd.clk_port->OUTSET = lcd.clk_pin;
    // }
    usart_spi_write(&usart, cmd);
}

void st7565r_write_array(unsigned char *array, size_t length)
{
    unsigned char page = 0;

    lcd.cs_port->OUTCLR = lcd.cs_pin;
    for (size_t i = 0; i < length; i++) {
        if (i % ST7565R_WIDTH == 0) {
            st7565r_set_page(page++);
            st7565r_set_column(0);
        }

        st7565r_write_data(array[i]);
    }
    lcd.cs_port->OUTSET = lcd.cs_pin;
}

void st7565r_clear(void)
{
}

void st7565r_position(unsigned char x, unsigned char y)
{
}

static void st7565r_set_page(unsigned char page)
{
    /* Make sure that the address is 4 bits (only 8 pages). */
    page &= 0x0F;
    st7565r_write_command(ST7565R_CMD_PAGE_SET(page));
}

static void st7565r_set_column(unsigned char column)
{
    /* Make sure the address is 7 bits. */
	column &= 0x7F;
	st7565r_write_command(ST7565R_CMD_COLUMN_SET_MSB(column >> 4));
	st7565r_write_command(ST7565R_CMD_COLUMN_SET_LSB(column & 0x0F));
}
