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

static unsigned char a4[] = { 255, 276, 297, 318, 338, 358, 377, 396, 413, 429, 444, 458, 470, 480, 490, 497, 503, 507, 509, 509, 508, 505, 500, 494, 485, 475, 464, 451, 437, 421, 404, 387, 368, 348, 328, 308, 286, 265, 244, 223, 201, 181, 161, 141, 122, 105, 88, 72, 58, 45, 34, 24, 15, 9, 4, 1, 0, 0, 2, 6, 12, 19, 29, 39, 51, 65, 80, 96, 113, 132, 151, 171, 191, 212, 233 };

static unsigned int counter = 0;

/* TIMER1 interrupt handler */
void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{
    // debug output to LEDs
    (*GPIO_PA_DOUT)++;

    /*
    *DAC0_CH0DATA = rand() % (1 << 12);
    *DAC0_CH1DATA = rand() % (1 << 12);
    */

    *DAC0_CH0DATA = a4[counter++ % 75];
    *DAC0_CH1DATA = a4[counter++ % 75];

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
