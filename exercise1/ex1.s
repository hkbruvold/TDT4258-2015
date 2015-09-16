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
	
	/// set high drive strength
	// load GPIO_CTRL to r2
	ldr r2, [r1, #GPIO_CTRL]

	// set high drive strength
	orr r2, r2, #0x2

	// store new value in memory
	str r2, [r1, #GPIO_CTRL]

	/// set pins to output
	// load GPIO_MODEH to r2
	//ldr r2, [r1, #GPIO_MODEH] not necessary

	// load data into r3
	ldr r3, =0x55555555

	// store data in GPIO_MODEH
	str r3, [r1, #GPIO_MODEH]

	//// set up button pins 0-7 ////
	// load base address for GPIO port C to r1
	ldr r1, =GPIO_PC_BASE

	/// set pins to input
	// load GPIO_MODEL to r2
	//ldr r2, [r1, #GPIO_MODEL] not necessary

	// load data to r3
	ldr r3, =0x33333333

	// store data to memory
	str r3, [r1, #GPIO_MODEL]

	/// enable pull-up on GPIO
	// load GPIO_PC_DOUT to r2
	ldr r2, [r1, #GPIO_DOUT]

	// modify data on r2
	orr r2, r2, #0xff

	// store data to memory
	str r2, [r1, #GPIO_DOUT]
	/////////////////////////////////////////////////////////////////////////////
	//
  // GPIO handler
  // The CPU will jump here when there is a GPIO interrupt
	//
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
gpio_handler:  

	      b .  // do nothing
	
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
dummy_handler:  
        b .  // do nothing

