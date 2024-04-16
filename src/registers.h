#ifndef __REGISTERS_H__
#define __REGISTERS_H__

// ATmega328P

// Page 72 - DDRB – The Port B Data Direction Register
#define DDRB *((volatile unsigned char*) 0x24)
// Page 72 - PORTB – The Port B Data Register
#define PORTB *((volatile unsigned char*) 0x25)
// LED is connected to Arduino Port 5
#define PORT_5 (1 << 5)

// Page 89 - 16-bit Timer/Counter1 with PWM

// Page 108 - TCCR1A – Timer/Counter1 Control Register A
#define TCCR1A *((volatile unsigned char*) 0x80)
// Waveform Generation Mode
#define WGM10 1
#define WGM11 1 << 1

// Page 110 - TCCR1B – Timer/Counter1 Control Register B
#define TCCR1B *((volatile unsigned char*) 0x81)
// Clock Select
#define CS10 1
#define CS11 1 << 1
#define CS12 1 << 2
#define WGM12 1 << 3
#define WGM13 1 << 4

// Page 112 - TIMSK1 – Timer/Counter1 Interrupt Mask Register
#define TIMSK1 *((volatile unsigned char*) 0x6F)
// Timer/Counter1, Overflow Interrupt Enable
#define TOIE1 1

// Page 111 - TCNT1H and TCNT1L – Timer/Counter1
#define TCNT1H *((volatile unsigned char*) 0x85)
#define TCNT1L *((volatile unsigned char*) 0x84)

// Page 113 - TIFR1 – Timer/Counter1 Interrupt Flag Register
#define TIFR1 *((volatile unsigned char*) 0x36)
// Timer/Counter1, Overflow Flag
#define TOV1 1

// Page 49 - Interrupt Vectors in ATmega328P
// Timer/Counter1 overflow
#define TIMER1_OVF __vector_13

// Page 37 - SMCR – Sleep Mode Control Register
#define SMCR *((volatile unsigned char*) 0x53)
// Sleep Mode
#define SM_IDLE 0
// Sleep Enable
#define SE 1

#endif