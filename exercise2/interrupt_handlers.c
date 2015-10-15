#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

#include "music.h"

#include "music_defs.c"

struct note_t
{
    unsigned short length;
    unsigned short samples[];
};

/* TIMER1 interrupt handler */
void __attribute__ ((interrupt)) LETIMER0_IRQHandler() 
{
    // debug output to LEDs
    (*GPIO_PA_DOUT)++;

    if (((*GPIO_PC_DIN) & 1) == 0)
        set_song(&test);

    play();

    *LETIMER0_IFC |= 1 << 2;
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

