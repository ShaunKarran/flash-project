
#include "usart_spi.h"

void usart_spi_init(struct USART_SPI_t *usart, USART_t *module, PORT_t *port)
{
    usart->module = module;
    usart->port   = port;

    usart->module->CTRLC = USART_CMODE_MSPI_gc | (1 << 1);
    usart->module->CTRLB = USART_TXEN_bm;

    usart->port->DIRSET = PIN3_bm | PIN1_bm;
}

void usart_spi_write(struct USART_SPI_t *usart, unsigned char data)
{
    while (!(usart->module->STATUS & USART_DREIF_bm));
    usart->module->DATA = data;
    while (!(usart->module->STATUS & USART_TXCIF_bm));
    usart->module->STATUS |= USART_TXCIF_bm;
}
