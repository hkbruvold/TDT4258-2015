#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

/* function to setup the timer */
void setupTimer(uint16_t period)
{
    *CMU_HFPERCLKEN0 |= 1 << 6;
    *TIMER1_TOP = period;
    *TIMER1_IEN |= 1;
    *TIMER1_CMD |= 1;
}
