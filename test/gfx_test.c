
#include <util/delay.h>

#include "cpu.h"
#include "gfx.h"
#include "lcd5110.h"

/* LCD pin definitions. */
#define LCD_DC  PIN2_bm
#define LCD_RST PIN3_bm
#define LCD_SCE SPI_SS_bm

int main(void)
{
    struct GFX_Buffer_t gfx;

    cpu_set_speed(CPU_32MHz);
    lcd5110_init(LCD5110_CONTRAST_MID, &PORTC, LCD_DC, LCD_RST, LCD_SCE);
    gfx_init(&gfx, LCD5110_WIDTH, LCD5110_HEIGHT, lcd5110_write_array);

    gfx_bind_buffer(&gfx);

    gfx_draw_string("Xmega is best!", ASCII_FONT, 0, 0);
    gfx_render();

    while (1);

    return 0;
}
