
#include "bitbang_spi.h"

void bitbang_spi_write(gpio_pin_t data_pin, gpio_pin_t clock_pin, uint8_t data)
{
    for (int i = 7; i > -1; i--) {
        gpio_clr_pin(clock_pin);
        if (get_bit(data, i)) {
            gpio_set_pin(data_pin);
        } else {
            gpio_clr_pin(data_pin);
        }
        gpio_set_pin(clock_pin);
    }
}
