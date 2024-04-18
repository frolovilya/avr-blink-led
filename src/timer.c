#include "timer.h"
#include "registers.h"

/*
    ---

    Page 244 - Fuse Low Byte
    "If 8MHz frequency exceeds the specification of the device (depends on VCC),
    the CKDIV8 fuse can be programmed in order to divide the internal frequency by 8."
    Page 261 - External Clock Drive
    < 4.5V - 8MHz
    5.5V - 16MHz

    Page 32 - System Clock Prescaler
    Page 33 - CLKPR – Clock Prescale Register
    Prescaling factor 8 can be changed via CLKPR register.
    CLKPS3..0 = 0011 = 8

    ---

    Page 25 - Clock Sources

    # Low power crystal oscillator
    ## (lfuse CKSEL3..0 = 1111)
    ## Arduino's 16MHz oscillator

    16bit timer = 2^16
    16*10^6 / 2^16 = 1 / overflow_time
    overflow_time ~= 4ms

    Page 110 - CS12..10 Clock Select
    with /256 timer prescaling (CS12..10 = 100)
    16*10^6 / 2^16 / 2^8 = 1 / overflow_time
    overflow_time ~= 1s

    ---

    # Calibrated internal RC oscillator
    ## (lfuse CKSEL3..0 = 0010)
    ## Built-in 8MHz oscillator

    8*10^6 / 2^16 / 2^8 = 1 / overflow_time
    overflow_time ~= 2s

    ---
*/

#define TIMER_OFFSET 34286

void setup_timer()
{
    // Page 109 - Waveform Generation Mode Bit Description
    // normal mode
    TCCR1A &= ~(WGM11 | WGM10);
    TCCR1B &= ~(WGM13 | WGM12);

    // /256 prescaling
    TCCR1B &= ~(CS11 | CS10);
    TCCR1B |= CS12;

    // overflow interrupt enabled
    TIMSK1 |= TOIE1;

    delay(1000);

    // Page 15 - Reset and Interrupt Handling
    // enabled interrupts globally
    __asm__ __volatile__("sei" ::: "memory");
}

void delay(unsigned short int time_ms)
{
    /*
    Page 111 - TCNT1H and TCNT1L – Timer/Counter1

    To get an exact overflow time (using internal oscillator):
    8*10^6 / ((2^16 - TCNT1) * 2^8) = 1 / (overflow_time_ms / 1000)
    (2^16 - TCNT1) * 2^8 = 8*10^6 * (overflow_time_ms / 1000)
    TCNT1 = 2^16 - 8*10^6 * (overflow_time_ms / 1000) / 2^8

    For simplicity, only allow up to 2 sec delay to avoid overflow.
    */
    time_ms = time_ms > 2000 ? 2000 : time_ms;
    unsigned short int timer_offset = 65536 - 31250 * (float)time_ms * 0.001;
    TCNT1 = timer_offset;
}