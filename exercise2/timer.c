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

void setupLETIMER()
{
  *CMU_OSCENCMD |= 1 << 8;

  // Select LFXO to drive LFACLK
  *CMU_LFCLKSEL &= ~0x3 << 0;
  *CMU_LFCLKSEL |= 2 << 0;
  *CMU_CTRL &= ~3 << 18;  

  // enable low energy peripherals in core clock
  *CMU_HFCORECLKEN0 |= 1 << 4;

  // enable clock for LETIMER
  *CMU_LFACLKEN0 |= 1 << 2;

  // set LETIMER0_COMP0 top register
  *LETIMER0_CTRL |= 1 << 9;

  // COMP0 set to 0 for one underflow interrupt per cycle
  *LETIMER0_COMP0 = 0x0;

  // start
  *LETIMER0_CMD |= 1 << 0;

  // enable interrupt
  *LETIMER0_IEN |= 1 << 2;
}
