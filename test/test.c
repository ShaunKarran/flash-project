
#include <stdlib.h>
#include <util/delay.h>

#include "cpu.h"
#include "fbuff.h"
#include "gl.h"
#include "gpio.h"
#include "ml.h"
#include "obj_type.h"
#include "st7565r.h"

#include "cube_manual.h"

int main(void) {
    float mv_matrix[4][4];
    char  x = 0, y = 0, z = 0;

    cpu_set_speed(CPU_32MHz);

    gpio_pin_t led0 = gpio_create_pin(&PORTR, PIN0_bm);
    gpio_set_output(led0);

    // gpio_pin_t lcd_data        = gpio_create_pin(&PORTD, PIN3_bm);
    // gpio_pin_t lcd_clock       = gpio_create_pin(&PORTD, PIN1_bm);
    // gpio_pin_t lcd_chip_select = gpio_create_pin(&PORTF, PIN3_bm);
    // gpio_pin_t lcd_a0          = gpio_create_pin(&PORTD, PIN0_bm);
    // gpio_pin_t lcd_reset       = gpio_create_pin(&PORTA, PIN3_bm);
    gpio_pin_t lcd_backlight   = gpio_create_pin(&PORTE, PIN4_bm);
    // gpio_set_output(lcd_data);
    // gpio_set_output(lcd_clock);
    // gpio_set_output(lcd_chip_select);
    // gpio_set_output(lcd_a0);
    // gpio_set_output(lcd_reset);
    gpio_set_output(lcd_backlight);

    gpio_set_pin(lcd_backlight);
    // st7565r_init(lcd_data, lcd_clock, lcd_chip_select, lcd_a0, lcd_reset);

    gl_init(ST7565R_WIDTH, ST7565R_HEIGHT, st7565r_write_array);
    // gl_orthographic(0, ST7565R_WIDTH - 1, ST7565R_HEIGHT - 1, 0, 10, 100);
    gl_perspective(-10, 10, 10, -10, 10, 50);

    while (1) {
        // ml_mat4_identity(mv_matrix);
        memset(mv_matrix, 0, 16 * sizeof(float));
        // mv_matrix[0][0] = 1; mv_matrix[1][1] = 1; mv_matrix[2][2] = 1; mv_matrix[3][3] = 1;
        mv_matrix[0][0] = 1; mv_matrix[0][1] = 0; mv_matrix[0][2] = 0; mv_matrix[0][3] = 0;
        mv_matrix[1][0] = 0; mv_matrix[1][1] = 1; mv_matrix[1][2] = 0; mv_matrix[1][3] = 0;
        mv_matrix[2][0] = 0; mv_matrix[2][1] = 0; mv_matrix[2][2] = 1; mv_matrix[2][3] = 0;
        mv_matrix[3][0] = 0; mv_matrix[3][1] = 0; mv_matrix[3][2] = 0; mv_matrix[3][3] = 1;

        // ml_translate(mv_matrix, x, y, z);
        // gl_bind_mvmatrix(mv_matrix);

        // gl_bind_vert_array(cube.vertices);
        // gl_bind_vert_index_array(&(*(cube.vertex_indices)));
        //
        // gl_draw_elements(cube.num_vertex_indices);

        gpio_tgl_pin(led0);
        _delay_ms(30); /* ~30fps */
    }

    return 0;
}
