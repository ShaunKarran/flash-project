
#include <util/delay.h>

#include "cpu.h"
#include "gfx.h"
#include "gpio.h"
#include "st7565r.h"

int main(void)
{
    struct GPIO_Pin_t led0;

    struct ST7565R_t    lcd;
    struct GPIO_Pin_t   lcd_data;
    struct GPIO_Pin_t   lcd_clk;
    struct GPIO_Pin_t   lcd_chip_select;
    struct GPIO_Pin_t   lcd_a0;
    struct GPIO_Pin_t   lcd_reset;
    struct GPIO_Pin_t   lcd_back_light;
    struct GFX_Buffer_t gfx;

    cpu_set_speed(CPU_32MHz);

    led0 = gpio_create_pin(&PORTR, PIN0_bm);
    gpio_set_output(&led0);

    lcd_data        = gpio_create_pin(&PORTD, PIN3_bm);
    lcd_clk         = gpio_create_pin(&PORTD, PIN1_bm);
    lcd_chip_select = gpio_create_pin(&PORTF, PIN3_bm);
    lcd_a0          = gpio_create_pin(&PORTD, PIN0_bm);
    lcd_reset       = gpio_create_pin(&PORTA, PIN3_bm);
    lcd_back_light  = gpio_create_pin(&PORTE, PIN4_bm);
    st7565r_init(&lcd, &USARTD0, &lcd_data, &lcd_clk, &lcd_chip_select, &lcd_a0, &lcd_reset, &lcd_back_light);

    gfx_init(&gfx, ST7565R_WIDTH, ST7565R_HEIGHT, st7565r_write_array);
    gfx_bind_buffer(&gfx);

    short i = 0;
    while (1) {
        if (i > 132) { i = 0; }
        gfx_clear();
        gfx_draw_circle(i++, 16, 10);
        gfx_render();

        gpio_tgl_pin(&led0);
        _delay_ms(100);
    }

    return 0;
}
