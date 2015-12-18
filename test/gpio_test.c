
#include <util/delay.h>

#include "cpu.h"
#include "gpio.h"

#define LED0_bm PIN0_bm
#define LED1_bm PIN1_bm
#define LED_PORT PORTR

int main(void)
{
    struct GPIO_Pin_t led0;

    led0 = gpio_create_pin(&LED_PORT, LED0_bm);

    gpio_set_output(&led0);

    gpio_clr_pin(&led0);

    while (1);

    return 0;
}
