
#include <stdlib.h>
#include <util/delay.h>

#include "cpu.h"
#include "fbuff.h"
#include "gl2d.h"
#include "gpio.h"
#include "ml.h"
#include "st7565r.h"

#define NUM_VERTICES 5

int main(void) {
    vec2_t vertex_array[NUM_VERTICES];
    mat3_t mv_matrix;

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

    gpio_set_pin(lcd_backlight);
    st7565r_init(lcd_data, lcd_clock, lcd_chip_select, lcd_a0, lcd_reset);

    gpio_pin_t led0 = gpio_create_pin(&PORTR, PIN0_bm);
    gpio_set_output(led0);

    gl2d_init(ST7565R_WIDTH, ST7565R_HEIGHT, st7565r_write_array);
    gl2d_orthographic(0, ST7565R_WIDTH - 1, ST7565R_HEIGHT - 1, 0);

    /* Defines the verticies to draw. */
    vertex_array[0].values[0] =  0;
    vertex_array[0].values[1] =  0;
    vertex_array[1].values[0] = 70;
    vertex_array[1].values[1] =  0;
    vertex_array[2].values[0] = 70;
    vertex_array[2].values[1] = 40;
    vertex_array[3].values[0] =  0;
    vertex_array[3].values[1] = 40;
    vertex_array[4].values[0] =  0;
    vertex_array[4].values[1] =  0;

    struct FBUFF_Buffer_t f_buffer;
    fbuff_init(&f_buffer, 132, 32);

    char i = 0;
    while (1) {
        ml_mat3_identity(&mv_matrix);
        mv_matrix.values[0][2] = 0; // Move i in x direction.
        mv_matrix.values[1][2] = i; // Move i in y direction.
        i++;

        // gl2d_bind_vertex_array(vertex_array, NUM_VERTICES);
        gl2d_bind_mvmatrix(mv_matrix);

        gl2d_draw(NUM_VERTICES);

        fbuff_fill(&f_buffer);
        st7565r_write_array(f_buffer.buffer, f_buffer.size);

        gpio_tgl_pin(led0);
        _delay_ms(30); /* ~30fps */
    }

    return 0;
}
