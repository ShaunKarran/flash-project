
#pragma once

#include <avr/io.h>
#include <stdint.h>

typedef enum { CPU_2MHZ, CPU_32MHz } cpu_speed_t;

void cpu_set_speed(cpu_speed_t speed);
