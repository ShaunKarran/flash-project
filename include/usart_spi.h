
#ifndef _USART_SPI_H_
#define _USART_SPI_H_

#include <avr/io.h>
#include <stdbool.h>

void usart_spi_init(USART_t *module);

void usart_spi_write(USART_t *module, unsigned char data);

#endif /* _USART_SPI_H_ */
