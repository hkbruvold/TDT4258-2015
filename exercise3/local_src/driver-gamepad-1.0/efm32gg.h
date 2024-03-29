#ifndef EFM32GG_H
#define EFM32GG_H

#define GPIO_MEM_INDEX       0
#define GPIO_EVEN_IRQ_INDEX  0
#define GPIO_ODD_IRQ_INDEX   1

#define GPIO_PC_BASE         0x48
#define GPIO_PC_LENGTH       (GPIO_PINLOCKN + 4)

#define GPIO_CTRL            0x00
#define GPIO_MODEL           0x04
#define GPIO_MODEH           0x08
#define GPIO_DOUT            0x0c
#define GPIO_DOUTSET         0x10
#define GPIO_DOUTCLR         0x14
#define GPIO_DOUTTGL         0x18
#define GPIO_DIN             0x1c
#define GPIO_PINLOCKN        0x20

#define GPIO_IRQ_BASE        0x100
#define GPIO_IRQ_LENGTH      (GPIO_IFC + 4)

#define GPIO_EXTIPSELL       0x00
#define GPIO_EXTIPSELH       0x04
#define GPIO_EXTIRISE        0x08
#define GPIO_EXTIFALL        0x0c
#define GPIO_IEN             0x10
#define GPIO_IF              0x14
#define GPIO_IFS             0x18
#define GPIO_IFC             0x1c

#endif // EFM32GG_h

