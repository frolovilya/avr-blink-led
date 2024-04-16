#include "delay.h"
#include "registers.h"

void setup_timer() 
{
    // Page 109 - Waveform Generation Mode Bit Description
    // normal mode
    TCCR1A &= ~WGM10;
    TCCR1A &= ~WGM11;
    TCCR1B &= ~WGM12;
    TCCR1B &= ~WGM13;
    
    // /256 prescaling
    TCCR1B &= ~CS10;
    TCCR1B &= ~CS11;
    TCCR1B |= CS12;
    
    // overflow interrupt enabled
    TIMSK1 |= TOIE1;

    // Page 15 - Reset and Interrupt Handling
    // enabled interrupts globally
    __asm__ __volatile__ ("sei" ::: "memory");
}

void delay(volatile long timeMs) {
    while (timeMs > 0) {
        timeMs--;
    }
}