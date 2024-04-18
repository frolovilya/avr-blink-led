#include "registers.h"
#include "timer.h"
#include "sleep.h"

void setup()
{
    // Use B5 port for output
    DDRB |= PORT_5;
}

void loop()
{
    // blink LED on PORTB5
    PORTB ^= PORT_5;
    delay(1000);
}

// interrupt when Timer1 overflows
void TIMER1_OVF(void) __attribute__((__signal__, __used__, __externally_visible__));
void TIMER1_OVF(void)
{
    loop();
}

int main(int argc, char const *argv[])
{
    setup_timer();
    setup();

    while (1)
    {
        sleep_idle();
    }

    return 0;
}
