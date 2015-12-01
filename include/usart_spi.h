
#ifndef _USART_SPI_H_
#define _USART_SPI_H_

#include <avr/io.h>
#include <stdbool.h>

#define USART_SPI_TXD1_bm PIN7_bm
#define USART_SPI_XCK1_bm PIN5_bm

struct USART_SPI_t {
    USART_t *module;
    PORT_t  *port;
};

void usart_spi_init(struct USART_SPI_t *usart, USART_t *module, PORT_t *port);

void usart_spi_write(struct USART_SPI_t *usart, unsigned char data);

#endif /* _USART_SPI_H_ */
