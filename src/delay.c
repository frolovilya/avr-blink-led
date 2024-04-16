#include "delay.h"
#include "ports.h"

void delay(int ms) {
    for (int i = 0; i < 100000; i++) {
        DDRB |= PORT_5;
    }
}