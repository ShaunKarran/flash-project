
#include <stdlib.h>
#include <util/delay.h>

#include "cpu.h"
#include "gl2d.h"
#include "lcd5110.h"

/* LCD pin definitions. */
#define LCD_DC  PIN2_bm
#define LCD_RST PIN3_bm
#define LCD_SCE SPI_SS_bm

#define NUM_VERTICES 5

int main(void) {
    float vertex_array[NUM_VERTICES * 2];

    cpu_set_speed(CPU_32MHz);
    lcd5110_init(LCD5110_CONTRAST_MID, &PORTC, LCD_DC, LCD_RST, LCD_SCE);
    gl2d_init(LCD5110_WIDTH, LCD5110_HEIGHT, lcd5110_write_array);

    vertex_array[0] = 5;
    vertex_array[1] = 10;
    vertex_array[2] = 15;
    vertex_array[3] = 20;
    vertex_array[4] = 20;
    vertex_array[5] = 7;
    vertex_array[6] = 8;
    vertex_array[7] = 2;
    vertex_array[8] = 5;
    vertex_array[9] = 10;

    gl2d_bind_vertex_array(vertex_array);

    gl2d_draw(NUM_VERTICES * 2);

    while (1);

    return 0;
}
