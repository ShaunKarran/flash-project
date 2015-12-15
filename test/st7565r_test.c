
#include <util/delay.h>

#include "cpu.h"
#include "gfx.h"
#include "st7565r.h"

#define LED0 PIN0_bm
#define LED1 PIN1_bm

int main(void)
{
    struct GFX_Buffer_t gfx;

    cpu_set_speed(CPU_32MHz);
    st7565r_init();

    gfx_init(&gfx, ST7565R_WIDTH, ST7565R_HEIGHT, st7565r_write_array);

    gfx_bind_buffer(&gfx);

    short i = 0;
    while (1) {
        if (i > 132) { i = 0; }
        gfx_clear();
        gfx_draw_circle(i++, 16, 10);
        gfx_render();
        _delay_ms(100);
    }

    return 0;
}
