#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

void setupDAC()
{
  /*
    TODO enable and set up the Digital-Analog Converter
    
    1. Enable the DAC clock by setting bit 17 in CMU_HFPERCLKEN0
    2. Prescale DAC clock by writing 0x50010 to DAC0_CTRL
    3. Enable left and right audio channels by writing 1 to DAC0_CH0CTRL and DAC0_CH1CTRL
    4. Write a continuous stream of samples to the DAC data registers, DAC0_CH0DATA and DAC0_CH1DATA, for example from a timer interrupt
  */

    *CMU_HFPERCLKEN0 |= 1 << 17; // enable DAC clock
    *CMU_HFPERCLKEN0 |= 1 << 15; // enable PRS cloc
    *DAC0_CTRL = 0x70012; // 0x2: sine mode
    *PRS_CH0_CTRL = 0x80001; // PRS source TIMER0
    *DAC0_CH0CTRL = 5; // enable CH0 with PRSEN
    *DAC0_CH1CTRL = 5;
}
