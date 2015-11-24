
#ifndef _CPU_H_
#define _CPU_H_

#include <avr/io.h>

#define CPU_2MHz  0
#define CPU_32MHz 1

void cpu_set_speed(unsigned char speed);

#endif /* _CPU_H_ */
