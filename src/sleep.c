#include "sleep.h"
#include "registers.h"

void sleep_idle()
{
    // Page 38 - Sleep Mode Select, Sleep Enable
    SMCR = SM_IDLE;
    SMCR |= SE;
    __asm__ __volatile__("sleep"
                         "\n\t" ::);
    SMCR &= ~SE;
}