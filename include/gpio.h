
#ifndef _GPIO_H_
#define _GPIO_H_

#include <avr/io.h>

typedef struct GPIO_Pin_t {
    PORT_t *port;
    unsigned char pin_bm;
} gpio_pin_t;

gpio_pin_t gpio_create_pin(PORT_t *port, unsigned char pin_bm);

void gpio_set_output(gpio_pin_t pin);

void gpio_set_input(gpio_pin_t pin);

void gpio_set_pin(gpio_pin_t pin);

void gpio_clr_pin(gpio_pin_t pin);

void gpio_tgl_pin(gpio_pin_t pin);

#endif /* _GPIO_H_ */
