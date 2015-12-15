
#include <util/delay.h>

#include "cpu.h"
#include "gfx.h"
#include "st7565r.h"

#define LED0 PIN0_bm
#define LED1 PIN1_bm

int main(void)
{
    // struct GFX_Buffer_t gfx;

    cpu_set_speed(CPU_32MHz);
    st7565r_init();

    // gfx_init(&gfx, LCD5110_WIDTH, LCD5110_HEIGHT, lcd5110_write_array);

    // gfx_bind_buffer(&gfx);

    // gfx_draw_string("Xmega is best!", ASCII_FONT, 0, 0);
    // gfx_render();

    while (1) {
        st7565r_write_data(0xFF);
    }

    return 0;
}
