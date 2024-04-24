// we need to be able to do a couple things
#include "avr-arch.h"
// calculate baud rate
#define BAUDRATE(baud) ((F_CPU / (16UL * baud)) - 1)