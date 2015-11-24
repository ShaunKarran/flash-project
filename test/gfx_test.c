
#include <util/delay.h>

#include "cpu.h"
#include "gfx.h"
#include "lcd5110.h"

/* LCD pin definitions. */
#define LCD_DC  PIN2_bm
#define LCD_RST PIN3_bm
#define LCD_SCE SPI_SS_bm

void gfx_draw_array(short *array, size_t num_items)
{
    for (int i = 0; i < num_items - 2; i += 2) {
        gfx_draw_line(array[i], array[i + 1], array[i + 2], array[i + 3]);
    }
}

int main(void)
{
    struct GFX_Buffer_t gfx;

    cpu_set_speed(CPU_32MHz);
    lcd5110_init(LCD5110_CONTRAST_MID, &PORTC, LCD_DC, LCD_RST, LCD_SCE);
    gfx_init(&gfx, LCD5110_WIDTH, LCD5110_HEIGHT, lcd5110_write_array);

    gfx_bind_buffer(&gfx);

    // gfx_draw_string("Xmega is best!", ASCII_FONT, 0, 0);
    // gfx_render();

    short array[6] = {0, 0, 20, 5, 0, 10};
    gfx_draw_array(array, 6);
    gfx_render();

    while (1);

    return 0;
}
