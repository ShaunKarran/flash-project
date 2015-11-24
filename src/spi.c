
#include "spi.h"

void spi_init_master(struct SPI_Master_t *spi,
                     SPI_t               *module,
                     PORT_t              *port,
                     SPI_MODE_t          mode,
                     SPI_PRESCALER_t     prescaler,
                     bool                clk2x,
                     bool                lsb_first)
{
    spi->module = module;
    spi->port   = port;

    spi->module->CTRL = prescaler |
	                    (clk2x ? SPI_CLK2X_bm : 0) |    /* Double clock. */
	                    SPI_ENABLE_bm |
	                    (lsb_first ? SPI_DORD_bm  : 0) | /* Data order. */
	                    SPI_MASTER_bm |
	                    mode;

    spi->port->DIRSET = SPI_MOSI_bm | SPI_SS_bm | SPI_SCK_bm;
}

void spi_write(struct SPI_Master_t *spi, unsigned char data)
{
    spi->module->DATA = data;
    while (~spi->module->STATUS & SPI_IF_bm); /* Wait for write to complete. */
}

unsigned char spi_read(struct SPI_Master_t *spi)
{
    while (~spi->module->STATUS & SPI_IF_bm);
    return spi->module->DATA;
}
