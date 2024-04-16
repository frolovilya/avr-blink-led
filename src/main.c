#include "registers.h"
#include "delay.h"
#include "sleep.h"

void setup() {
  setup_timer();

  // Use B5 port for output
  DDRB |= PORT_5;
}

void TIMER1_OVF (void) __attribute__ ((__signal__, __used__, __externally_visible__));
void TIMER1_OVF (void)
{
  PORTB ^= PORT_5;
}

int main(int argc, char const *argv[])
{
    setup();

    while(1) {
      sleep();
    }
    
    return 0;
}
