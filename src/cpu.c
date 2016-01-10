
#include "cpu.h"

void cpu_set_speed(cpu_speed_t speed)
{
	switch (speed) {
		case CPU_32MHz:
			CCP = CCP_IOREG_gc;				 /* Disable protection (4 clock cycles). */
			OSC.CTRL = OSC_RC32MEN_bm;		 /* Enable the 32MHz internal clock. */
			while (~OSC.STATUS & OSC_RC32MRDY_bm);	/* Wait for clock to be ready. */
			CCP = CCP_IOREG_gc;				 /* Unsure wait time. Disable again. */
			CLK.CTRL = CLK_SCLKSEL_RC32M_gc; /* Select system clock. */
			break;

		default: /* 2MHz */
			CCP = CCP_IOREG_gc;
			OSC.CTRL = OSC_RC2MEN_bm;
			while (~OSC.STATUS & OSC_RC2MRDY_bm);
			CCP = CCP_IOREG_gc;
			CLK.CTRL = CLK_SCLKSEL_RC2M_gc;
			break;
	}
}
