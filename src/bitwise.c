
#include "bitwise.h"

inline void set_bit(uint8_t *reg, uint8_t bit)
{
    *reg |= (1 << bit);
}

inline void clr_bit(uint8_t *reg, uint8_t bit)
{
    *reg &= ~(1 << bit);
}

inline void tog_bit(uint8_t *reg, uint8_t bit)
{
    *reg ^= (1 << bit);
}

inline uint8_t get_bit(uint8_t reg, uint8_t bit)
{
    return reg &= (1 << bit);
}
