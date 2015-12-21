
#ifndef _BIGBANG_SPI_H_
#define _BIGBANG_SPI_H_

#include <avr/io.h>

#include "bitwise.h"
#include "gpio.h"

void bitbang_spi_write(gpio_pin_t data_pin, gpio_pin_t clock_pin, unsigned char data);

#endif /* _BIGBANG_SPI_H_ */
