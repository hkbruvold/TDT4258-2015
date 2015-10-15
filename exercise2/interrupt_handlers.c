#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

#include "music.h"

#include "music_defs.c"

#include "ex2.h"

/* TIMER interrupt handler */
#ifdef USE_LETIMER
void __attribute__ ((interrupt)) LETIMER0_IRQHandler()
#else
void __attribute__ ((interrupt)) TIMER1_IRQHandler()
#endif
{
    // debug output to LEDs
    (*GPIO_PA_DOUT)++;

    play();

#ifdef USE_LETIMER
    *LETIMER0_IFC |= 1 << 2;
#else
    *TIMER1_IFC |= 1;
#endif
}

/* Common GPIO handler function */
void gpio_handler()
{
    set_song(&test);
    start_timer();

    *GPIO_IFC = *GPIO_IF;
}

/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler()
{
    gpio_handler();
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler()
{
    gpio_handler();
}

