#ifndef STEP_MOTOR_H
#define STEP_MOTOR_H

#include <stdio.h>

void stepmotor_init( void );
void stepmotor_passos(uint32_t passos, uint8_t dir);

#endif