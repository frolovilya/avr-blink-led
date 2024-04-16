#include "delay.h"
#include "ports.h"

void delay(volatile long timeMs) {
    while (timeMs > 0) {
        timeMs--;
    }
}