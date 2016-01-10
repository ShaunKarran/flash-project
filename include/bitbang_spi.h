
#pragma once

#include <avr/io.h>
#include <stdint.h>

#include "bitwise.h"
#include "gpio.h"

void bitbang_spi_write(gpio_pin_t data_pin, gpio_pin_t clock_pin, uint8_t data);
