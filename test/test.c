
#include <util/delay.h>

#include "cpu.h"
#include "gfx.h"
#include "gpio.h"
#include "st7565r.h"

int main(void)
{
    struct GFX_Buffer_t gfx;

    cpu_set_speed(CPU_32MHz);

    gpio_pin_t lcd_data        = gpio_create_pin(&PORTD, PIN3_bm);
    gpio_pin_t lcd_clock       = gpio_create_pin(&PORTD, PIN1_bm);
    gpio_pin_t lcd_chip_select = gpio_create_pin(&PORTF, PIN3_bm);
    gpio_pin_t lcd_a0          = gpio_create_pin(&PORTD, PIN0_bm);
    gpio_pin_t lcd_reset       = gpio_create_pin(&PORTA, PIN3_bm);
    gpio_pin_t lcd_backlight   = gpio_create_pin(&PORTE, PIN4_bm);
    gpio_set_output(lcd_data);
    gpio_set_output(lcd_clock);
    gpio_set_output(lcd_chip_select);
    gpio_set_output(lcd_a0);
    gpio_set_output(lcd_reset);
    gpio_set_output(lcd_backlight);

    st7565r_init(&USARTD0, lcd_chip_select, lcd_a0, lcd_reset);
    gpio_set_pin(lcd_backlight);

    gpio_pin_t led0 = gpio_create_pin(&PORTR, PIN0_bm);
    gpio_set_output(led0);

    gfx_init(&gfx, ST7565R_WIDTH, ST7565R_HEIGHT, st7565r_write_array);
    gfx_bind_buffer(&gfx);

    short i = 0;
    while (1) {
        if (i > 132) { i = 0; }
        gfx_clear();
        gfx_draw_circle(i++, 16, 10);
        gfx_render();

        gpio_tgl_pin(led0);
        _delay_ms(30);
    }

    return 0;
}
