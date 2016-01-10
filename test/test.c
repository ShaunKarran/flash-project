
#include <stdint.h>
#include <stdlib.h>
#include <util/delay.h>

#include "cpu.h"
#include "fbuff.h"
#include "gl.h"
// #include "gfx.h"
#include "gpio.h"
#include "ml.h"
#include "st7565r.h"

#include "cube_manual.h"

int main(void) {
    cpu_set_speed(CPU_32MHz);

    gpio_pin_t led0 = gpio_create_pin(&PORTR, PIN0_bm);
    gpio_set_output(led0);

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

    struct FBUFF_Buffer_t frame_buffer;
    fbuff_init(&frame_buffer, ST7565R_WIDTH, ST7565R_HEIGHT);

    gl_init(&frame_buffer, st7565r_write_array);
    gl_viewport(0, 0, ST7565R_WIDTH, ST7565R_HEIGHT);
    gl_perspective(-10, 10, 10, -10, 10, 50);
    // gl_orthographic(-10, 10, -10, 10, 10, 50);

    float mv_matrix[4][4];
    gl_bind_mvmatrix(mv_matrix);

    int8_t  x = 0, y = 0, z = 0;
    while (1) {
        ml_mat4_identity(mv_matrix);

        ml_translate(mv_matrix, x, y, z);

        gl_bind_vert_array(cube.vertices);
        gl_bind_vert_index_array(cube.vertex_indices);

        gl_draw_elements(cube.num_vertex_indices);

        gpio_tgl_pin(led0);
        // _delay_ms(30); /* ~30fps */
    }

    return 0;
}
