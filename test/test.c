
#include <stdint.h>
#include <stdlib.h>
#include <util/delay.h>

#include "cpu.h"
#include "fbuf.h"
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

    struct FBUF_Buffer_t frame_buffer;
    fbuf_init(&frame_buffer, ST7565R_WIDTH, ST7565R_HEIGHT);

    gl_init(&frame_buffer, st7565r_write_array);
    gl_viewport(0, 0, ST7565R_WIDTH, ST7565R_HEIGHT);
    gl_perspective(-10, 10, 10, -10, 10, 50);
    // gl_orthographic(-10, 10, -10, 10, 10, 50);

    float mv_matrix[4][4];
    gl_bind_mvmatrix(mv_matrix);

    int8_t  x1 = -1, x2 = 0, x3 = 1, z = -2;
    float   rotx = 0, roty = 0, rotz = 0;
    while (1) {
        gl_bind_vert_array(cube.vertices);
        gl_bind_vert_index_array(cube.vertex_indices);

        rotx = (rotx > 360) ? 0 : rotx + 1;
        roty = (roty > 360) ? 0 : roty + 1;
        rotz = (rotz > 360) ? 0 : rotz + 1;

        ml_mat4_identity(mv_matrix);
        ml_rotate_x(mv_matrix, rotx);
        ml_translate(mv_matrix, x1, 0, z);
        gl_draw_elements(cube.num_vertex_indices);

        ml_mat4_identity(mv_matrix);
        ml_rotate_y(mv_matrix, roty);
        ml_translate(mv_matrix, x2, 0, z);
        gl_draw_elements(cube.num_vertex_indices);

        ml_mat4_identity(mv_matrix);
        ml_rotate_z(mv_matrix, rotz);
        ml_translate(mv_matrix, x3, 0, z);
        gl_draw_elements(cube.num_vertex_indices);

        st7565r_write_array(frame_buffer.data, frame_buffer.size);
        fbuf_clear(&frame_buffer);

        gpio_tgl_pin(led0);
        // _delay_ms(30); /* ~30fps */
    }

    return 0;
}
