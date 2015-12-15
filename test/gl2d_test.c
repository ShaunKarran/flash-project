
#include <stdlib.h>
#include <util/delay.h>

#include "cpu.h"
#include "gl2d.h"
// #include "lcd5110.h"
#include "ml.h"
#include "st7565r.h"

/* LED pins for debugging. */
#define LED0        PIN0_bm
#define LED1        PIN1_bm
#define LED_PORT    PORTR

/* LCD pin definitions. */
#define LCD_DC  PIN2_bm
#define LCD_RST PIN3_bm
#define LCD_SCE SPI_SS_bm

#define NUM_VERTICES 5

int main(void) {
    vec2_t vertex_array[NUM_VERTICES];
    mat3_t mv_matrix;

    LED_PORT.DIRSET = LED0;

    cpu_set_speed(CPU_32MHz);

    // lcd5110_init(LCD5110_CONTRAST_MID, &PORTC, LCD_DC, LCD_RST, LCD_SCE);
    // gl2d_init(LCD5110_WIDTH, LCD5110_HEIGHT, lcd5110_write_array);
    st7565r_init();
    gl2d_init(ST7565R_WIDTH, ST7565R_HEIGHT, st7565r_write_array);

    // gl2d_orthographic(0, LCD5110_WIDTH - 1, LCD5110_HEIGHT - 1, 0);
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

    char i = 0;
    while (1) {
        gl2d_clear_buffer();

        ml_mat3_identity(&mv_matrix);
        mv_matrix.values[0][2] = 0; // Move i in x direction.
        mv_matrix.values[1][2] = i; // Move i in y direction.
        i++;

        gl2d_bind_vertex_array(vertex_array, NUM_VERTICES * 2);
        gl2d_bind_mvmatrix(&mv_matrix);

        gl2d_draw(NUM_VERTICES);

        LED_PORT.OUTTGL = LED0;
        _delay_ms(100);
    }

    return 0;
}
