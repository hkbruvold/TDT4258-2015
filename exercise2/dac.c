#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

void setupDAC()
{
    *CMU_HFPERCLKEN0 |= 1 << 17; // enable DAC clock
    *DAC0_CTRL = 0x50010;
    *DAC0_CH0CTRL = 1;
    *DAC0_CH1CTRL = 1;
}
