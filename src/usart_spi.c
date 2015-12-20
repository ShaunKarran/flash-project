
#include "usart_spi.h"

void usart_spi_init(USART_t *module)
{
    module->CTRLC = USART_CMODE_MSPI_gc | (1 << 1);
    module->CTRLB = USART_TXEN_bm;
}

void usart_spi_write(USART_t *module, unsigned char data)
{
    while (!(module->STATUS & USART_DREIF_bm));
    module->DATA = data;
    while (!(module->STATUS & USART_TXCIF_bm));
    module->STATUS |= USART_TXCIF_bm;
}
