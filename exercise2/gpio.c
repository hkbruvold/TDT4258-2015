#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

/* function to set up GPIO mode and interrupts*/
void setupGPIO()
{
  *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_GPIO; /* enable GPIO clock*/

  /* Enable LEDs */
  *GPIO_PA_CTRL = 2;  /* set high drive strength */
  *GPIO_PA_MODEH = 0x55555555; /* set pins A8-15 as output */

  /* Enable buttons */
  *GPIO_PC_MODEL = 0x33333333; /* set pins to input with filter*/
  *GPIO_PC_DOUT |= 0xFF; /* set pin to be pull-up */

  /* Enable interrupt */
  *GPIO_EXTIPSELL = 0x22222222; /* set external interrupt to use pin 0-7 port C */
  *GPIO_EXTIFALL = 0xFF; /* fire interrupt on falling edge */
  *GPIO_EXTIRISE = 0xFF; /* fire interrupt on rising edge */
  *GPIO_IEN = 0xFF; /* enable GPIO external interrupt 0-7 */
}
