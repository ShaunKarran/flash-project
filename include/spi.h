
#pragma once

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

#define SPI_SS_bm   PIN4_bm
#define SPI_MOSI_bm PIN5_bm
#define SPI_MISO_bm PIN6_bm
#define SPI_SCK_bm  PIN7_bm

struct SPI_Master_t {
    SPI_t  *module;
    PORT_t *port;
};

void spi_init_master(struct SPI_Master_t *spi,
                     SPI_t               *module,
                     PORT_t              *port,
                     SPI_MODE_t          mode,
                     SPI_PRESCALER_t     prescaler,
                     bool                clk2x,
                     bool                lsb_first);

void spi_write(struct SPI_Master_t *spi, uint8_t data);

uint8_t spi_read(struct SPI_Master_t *spi);
