
#include <stdlib.h>
#include <util/delay.h>

#include "cpu.h"
#include "gl2d.h"
#include "lcd5110.h"
#include "ml.h"

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
    float vertex_array[NUM_VERTICES * 2];
    mat3_t mv_matrix;

    cpu_set_speed(CPU_32MHz);

    LED_PORT.DIRSET = LED0;

    lcd5110_init(LCD5110_CONTRAST_MID, &PORTC, LCD_DC, LCD_RST, LCD_SCE);
    gl2d_init(LCD5110_WIDTH, LCD5110_HEIGHT, lcd5110_write_array);
    gl2d_orthographic(0, LCD5110_WIDTH, 0, LCD5110_HEIGHT);

    /* Each pair of values defines a vertex in the square. */
    vertex_array[0] = 37;
    vertex_array[1] = 19;
    vertex_array[2] = 47;
    vertex_array[3] = 19;
    vertex_array[4] = 47;
    vertex_array[5] = 29;
    vertex_array[6] = 37;
    vertex_array[7] = 29;
    vertex_array[8] = 37;
    vertex_array[9] = 19;

    char i = 0;
    while (1) {
        gl2d_clear_buffer();

        ml_mat3_identity(&mv_matrix);
        // mv_matrix.values[0][2] = i; // Move i in x direction.
        // mv_matrix.values[1][2] = i; // Move i in y direction.
        // i++;

        gl2d_bind_vertex_array(vertex_array, NUM_VERTICES * 2);
        gl2d_bind_mvmatrix(&mv_matrix);

        gl2d_draw(NUM_VERTICES);

        LED_PORT.OUTTGL = LED0;
        _delay_ms(100);
    }

    return 0;
}
