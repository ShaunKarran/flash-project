// Information ----------------------------------------------------------------

/*	Library:		libXmegaA
 *	Purpose:		Bitwise macros
 *	Author(s):		Shaun Karran
 *	Created:		November 2015
*/

#pragma once

#include <stdint.h>

// Macros ----------------------------------------------------------------

void set_bit(uint8_t *reg, uint8_t bit);

void clr_bit(uint8_t *reg, uint8_t bit);

void tog_bit(uint8_t *reg, uint8_t bit);

uint8_t get_bit(uint8_t reg, uint8_t bit);
