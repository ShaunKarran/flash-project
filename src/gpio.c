
#include "gpio.h"

struct GPIO_Pin_t gpio_create_pin(PORT_t *port, unsigned char pin_bm)
{
    struct GPIO_Pin_t pin;

    pin.port = port;
    pin.pin_bm = pin_bm;

    return pin;
}

void gpio_set_output(struct GPIO_Pin_t *pin)
{
    pin->port->DIRSET = pin->pin_bm;
}

void gpio_set_input(struct GPIO_Pin_t *pin)
{
    pin->port->DIRCLR = pin->pin_bm;
}

void gpio_set_pin(struct GPIO_Pin_t *pin)
{
    pin->port->OUTSET = pin->pin_bm;
}

void gpio_clr_pin(struct GPIO_Pin_t *pin)
{
    pin->port->OUTCLR = pin->pin_bm;
}

void gpio_tgl_pin(struct GPIO_Pin_t *pin)
{
    pin->port->OUTTGL = pin->pin_bm;
}
