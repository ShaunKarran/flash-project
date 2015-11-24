
#include <util/delay.h>
#include <avr/interrupt.h>

#include "cpu.h"
#include "gfx.h"
#include "lcd5110.h"

/* LCD pin definitions. */
#define LCD_DC  PIN2_bm
#define LCD_RST PIN3_bm
#define LCD_SCE SPI_SS_bm

#define SW0_PORT PORTE
#define SW1_PORT PORTF
#define SW0  PIN5_bm
#define SW1  PIN1_bm

static short x = 0;
static short y = 40;

ISR (PORTE.INT0_vect)
{
    x++;
}

int main(void)
{
    struct GFX_Buffer_t gfx;
    struct GFX_Sprite_t tank;
    unsigned char tank_bitmap[] = {0xC0, 0xC0, 0xE0, 0xC0, 0xC0};

    cpu_set_speed(CPU_32MHz);

    /* Set direction registers for switches. */
    SW0_PORT.DIRCLR = SW0;
    SW1_PORT.DIRCLR = SW1;

    SW0_PORT.PIN5CTRL = PORT_ISC_FALLING_gc;
    SW0_PORT.INT0MASK = SW0; /* SW0 triggers INT0. */
    SW0_PORT.INTCTRL = PORT_INT0LVL_HI_gc;
    PMIC.CTRL = PMIC_HILVLEN_bm;

    lcd5110_init(LCD5110_CONTRAST_MID, &PORTC, LCD_DC, LCD_RST, LCD_SCE);
    gfx_init(&gfx, LCD5110_WIDTH, LCD5110_HEIGHT, lcd5110_write_array);

    gfx_bind_buffer(&gfx);

    gfx_init_sprite(&tank, tank_bitmap, 5, 8);

    sei();
    for (;;) {
        gfx_clear();
        gfx_draw_sprite(&tank, x, y);
        gfx_render();
    }
    cli();

    return 0;
}
