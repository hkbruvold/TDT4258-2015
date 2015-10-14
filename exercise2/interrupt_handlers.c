#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

static unsigned int next = 1;

int rand_r(unsigned int *seed)
{
       *seed = *seed * 1103515245 + 12345;
       return (*seed % ((unsigned int)(1<<31) + 1));
}

int rand(void)
{
       return (rand_r(&next));
}

void srand(unsigned int seed)
{
       next = seed;
}

/* TIMER1 interrupt handler */
void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{
    // debug output to LEDs
    (*GPIO_PA_DOUT)++;

    *DAC0_CH0DATA = rand() % (1 << 12);
    *DAC0_CH1DATA = rand() % (1 << 12);

    *TIMER1_IFC = 1;
}

/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() 
{
    *GPIO_IFC = *GPIO_IF;
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() 
{
    *GPIO_IFC = *GPIO_IF;
}
