// Information ----------------------------------------------------------------

/*	Library:		libXmegaA
 *	Purpose:		Bitwise macros
 *	Author(s):		Shaun Karran
 *	Created:		November 2015
*/

#ifndef _bitwise_h_
#define _bitwise_h_

// Macros ----------------------------------------------------------------

#define set_bit(reg, bit) (reg |= (1 << bit))
#define clr_bit(reg, bit) (reg &= ~(1 << bit))
#define tog_bit(reg, bit) (reg ^= (1 << bit))
#define get_bit(reg, bit) (reg & (1 << bit))

#endif // _bitwise_h_
