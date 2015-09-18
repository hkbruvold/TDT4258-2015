.syntax unified
.include "efm32gg.s"

/////////////////////////////////////////////////////////////////////////////
//
// Exception vector table
// This table contains addresses for all exception handlers
//
/////////////////////////////////////////////////////////////////////////////
.section .vectors

.long   stack_top               /* Top of Stack                 */
.long   _reset                  /* Reset Handler                */
.long   dummy_handler           /* NMI Handler                  */
.long   dummy_handler           /* Hard Fault Handler           */
.long   dummy_handler           /* MPU Fault Handler            */
.long   dummy_handler           /* Bus Fault Handler            */
.long   dummy_handler           /* Usage Fault Handler          */
.long   dummy_handler           /* Reserved                     */
.long   dummy_handler           /* Reserved                     */
.long   dummy_handler           /* Reserved                     */
.long   dummy_handler           /* Reserved                     */
.long   dummy_handler           /* SVCall Handler               */
.long   dummy_handler           /* Debug Monitor Handler        */
.long   dummy_handler           /* Reserved                     */
.long   dummy_handler           /* PendSV Handler               */
.long   dummy_handler           /* SysTick Handler              */

/* External Interrupts */
.long   dummy_handler
.long   gpio_handler            /* GPIO even handler */
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   gpio_handler            /* GPIO odd handler */
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler
.long   dummy_handler

.section .text

/////////////////////////////////////////////////////////////////////////////
//
// Reset handler
// The CPU will start executing here after a reset
//
/////////////////////////////////////////////////////////////////////////////

.globl  _reset
.type   _reset, %function

.thumb_func
_reset:
    //// start GPIO clocks ////
    // load base address to r1
    ldr r1, =CMU_BASE

    // load HFPERCLK to r2
    ldr r2, [r1, #CMU_HFPERCLKEN0]

    // set GPIO bit
    mov r3, #1
    lsl r3, r3, #CMU_HFPERCLKEN0_GPIO
    orr r2, r2, r3

    // store value in memory
    str r2, [r1, #CMU_HFPERCLKEN0]

    //// set up LED pins 8-15 ////
    // load base address for GPIO port A to r1
    ldr r1, =GPIO_PA_BASE

    // set high drive strength bit (0x2)
    ldr r2, [r1, #GPIO_CTRL]
    orr r2, r2, #0x2
    str r2, [r1, #GPIO_CTRL]

    /// set pins to output
    mov r3, #0x55555555
    str r3, [r1, #GPIO_MODEH]

    //// set up button pins 0-7 ////
    // load base address for GPIO port C to r1
    ldr r1, =GPIO_PC_BASE

    /// set pins to input
    // load data to r3
    mov r3, #0x33333333
    str r3, [r1, #GPIO_MODEL]

    // enable pull-up on pins
    ldr r2, [r1, #GPIO_DOUT]
    orr r2, r2, #0xff
    str r2, [r1, #GPIO_DOUT]

    //// GPIO interrupts ////
    ldr r1, =GPIO_BASE
    mov r3, #0x22222222
    str r3, [r1, #GPIO_EXTIPSELL]

    mov r3, #0xFF
    // interrupt on falling edge
    str r3, [r1, #GPIO_EXTIFALL]
    // interrupt on rising edge
    str r3, [r1, #GPIO_EXTIRISE]
    // enable GPIO interrupts
    str r3, [r1, #GPIO_IEN]

    // enable interrupt handling (write 0x802 to ISER0)
    movw r3, #0x802
    ldr r1, =ISER0
    str r3, [r1]

    // enable deep sleep and automatic sleep
    ldr r1, =SCR
    mov r2, #6
    str r2, [r1]

    // enter sleep
    wfi

/////////////////////////////////////////////////////////////////////////////
//
// GPIO handler
// The CPU will jump here when there is a GPIO interrupt
//
/////////////////////////////////////////////////////////////////////////////

.thumb_func
gpio_handler:
    // load led and button base memory to register
    ldr r1, =GPIO_PA_BASE
    ldr r2, =GPIO_PC_BASE

    // load offset for reading and writing for button and led
    ldr r3, [r2, #GPIO_DIN]
    /* because the LED outputs are on pin 8-15 and input is on pins 0-7, we
     * shift the input 8 bits to the left */
    lsl r3, 8

    // write button data to led
    str r3, [r1, #GPIO_DOUT]

    // clear the interrupt
    ldr r1, =GPIO_BASE
    ldr r2, [r1, #GPIO_IF]
    str r2, [r1, #GPIO_IFC]

    // return
    bx r14

.thumb_func
dummy_handler:
    // do nothing
    b .

