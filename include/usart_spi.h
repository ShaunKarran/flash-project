
#pragma once

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

void usart_spi_init(USART_t *module);

void usart_spi_write(USART_t *module, uint8_t data);
