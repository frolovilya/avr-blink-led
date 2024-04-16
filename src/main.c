#include "ports.h"
#include "delay.h"

void setup() {
  // Use B5 port for output
  DDRB |= PORT_5;
}

void loop() {
  PORTB |= PORT_5;
  delay(500);
  PORTB &= ~PORT_5;
  delay(1000);
}

int main(int argc, char const *argv[])
{
    setup();

    while(1) {
        loop();
    }
    
    return 0;
}
