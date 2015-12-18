
#ifndef _GPIO_H_
#define _GPIO_H_

#include <avr/io.h>

struct GPIO_Pin_t {
    PORT_t *port;
    unsigned char pin_bm;
};

struct GPIO_Pin_t gpio_create_pin(PORT_t *port, unsigned char pin_bm);

void gpio_set_output(struct GPIO_Pin_t *pin);

void gpio_set_input(struct GPIO_Pin_t *pin);

void gpio_set_pin(struct GPIO_Pin_t *pin);

void gpio_clr_pin(struct GPIO_Pin_t *pin);

void gpio_tgl_pin(struct GPIO_Pin_t *pin);

#endif /* _GPIO_H_ */
