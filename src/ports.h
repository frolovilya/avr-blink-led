#ifndef __PORTS_H__
#define __PORTS_H__

// ATmega328P

// Port B Data Direction Register
#define DDRB *((volatile unsigned char*) 0x24)
// Port B Data Register
#define PORTB *((volatile unsigned char*) 0x25)

#define PORT_5 (1 << 5)

#endif