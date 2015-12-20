
#include "gpio.h"

gpio_pin_t gpio_create_pin(PORT_t *port, unsigned char pin_bm)
{
    gpio_pin_t pin;

    pin.port = port;
    pin.pin_bm = pin_bm;

    return pin;
}

void gpio_set_output(gpio_pin_t pin)
{
    pin.port->DIRSET = pin.pin_bm;
}

void gpio_set_input(gpio_pin_t pin)
{
    pin.port->DIRCLR = pin.pin_bm;
}

void gpio_set_pin(gpio_pin_t pin)
{
    pin.port->OUTSET = pin.pin_bm;
}

void gpio_clr_pin(gpio_pin_t pin)
{
    pin.port->OUTCLR = pin.pin_bm;
}

void gpio_tgl_pin(gpio_pin_t pin)
{
    pin.port->OUTTGL = pin.pin_bm;
}
