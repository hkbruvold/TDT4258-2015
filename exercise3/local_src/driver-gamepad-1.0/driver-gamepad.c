#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/ioport.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include <asm/uaccess.h>

#include "efm32gg.h"

#define NUM_MINOR (1)
#define DEVICE_NAME ("gamepad")

// device structs
static dev_t device_number;
static struct cdev char_device;
static struct class *cl;

// mapped memory addresses
static void *gpio_pc;
static void *gpio_irq;

// open count for device file
static unsigned int dev_open_count = 0;

// cached GPIO pin data
static char button_data;

// function declarations
static int gamepad_open(struct inode *inode, struct file *filp);
static int gamepad_release(struct inode *inode, struct file *filp);
static ssize_t gamepad_read(struct file *filp, char __user *buff,
                            size_t count, loff_t *offp);
static int __init gpio_init(void);
static void __exit gpio_exit(void);
static int __init gamepad_init(void);
static void __exit gamepad_exit(void);

static irqreturn_t gpio_handler(int irq, void *dev_id);

// file operations for the device
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = gamepad_open,
    .release = gamepad_release,
    .read = gamepad_read,
};

// GPIO interrupt handler
static irqreturn_t gpio_handler(int irq, void *dev_id)
{
    // cache button data
    button_data = ioread8(gpio_pc + GPIO_DIN);

    // clear the interrupt: write value of GPIO_IF to GPIO_IFC
    iowrite32(ioread32(gpio_pc + GPIO_IF), gpio_pc + GPIO_IFC);

    return IRQ_HANDLED;
}

static int __init gpio_init(void)
{
    // request exclusive access to the GPIO port C memory region
    if (request_mem_region(GPIO_PC_BASE, GPIO_PC_LENGTH, DEVICE_NAME) == NULL)
        return -EBUSY; // "device or resource busy"

    // map the GPIO port C ports to memory
    gpio_pc = ioremap_nocache(GPIO_PC_BASE, GPIO_PC_LENGTH);

    // request and map GPIO IRQ region
    if (request_mem_region(GPIO_IRQ_BASE, GPIO_IRQ_LENGTH, DEVICE_NAME) == NULL)
        return -EBUSY;
    gpio_irq = ioremap_nocache(GPIO_IRQ_BASE, GPIO_PC_LENGTH);

    // set pins to input with filter
    iowrite32(0x33333333, gpio_pc + GPIO_MODEL);

    // set pins to be pull-up
    iowrite32(0xff, gpio_pc + GPIO_DOUT);

    // set interrupt to use port C
    iowrite32(0x22222222, gpio_irq + GPIO_EXTIPSELL);

    // set interrupts to fire on rising and falling edge for pins 0-7
    iowrite32(0xf, gpio_irq + GPIO_EXTIRISE);
    iowrite32(0xf, gpio_irq + GPIO_EXTIFALL);

    return 0;
}

static void __exit gpio_exit(void)
{
    // unmap and release memory regions
    iounmap(gpio_pc);
    iounmap(gpio_irq);
    release_mem_region(GPIO_PC_BASE, GPIO_PC_LENGTH);
    release_mem_region(GPIO_IRQ_BASE, GPIO_IRQ_LENGTH);
}

static int gamepad_open(struct inode *inode, struct file *filp)
{
    int err;

    if (dev_open_count == 0) // first open, enable interrupts
    {
        // request IRQ lines
        err = request_irq(GPIO_EVEN_IRQ_NUM, &gpio_handler, 0, DEVICE_NAME, NULL);
        if (err < 0)
            return err;
        err = request_irq(GPIO_ODD_IRQ_NUM, &gpio_handler, 0, DEVICE_NAME, NULL);
        if (err < 0)
            return err;

        // enable GPIO interrupts for pin 0-7
        iowrite32(0xf, gpio_irq + GPIO_IEN);
    }

    ++dev_open_count;

    return 0;
}

static int gamepad_release(struct inode *inode, struct file *filp)
{
    --dev_open_count;

    if (dev_open_count == 0) // disable interrupts on final release
    {
        iowrite32(0x0, gpio_irq + GPIO_IEN);

        free_irq(GPIO_EVEN_IRQ_NUM, NULL);
        free_irq(GPIO_ODD_IRQ_NUM, NULL);
    }

    return 0;
}

/*
 * Note: The functions we introduce in this section and in "Using the ioctl
 * Argument" in Chapter 5, "Enhanced Char Driver Operations" use some hidden
 * magic to deal with page faults in the proper way even when the CPU is
 * executing in kernel space.
 */

static ssize_t gamepad_read(struct file *filp, char __user *buff,
                            size_t count, loff_t *offp)
{
    // write a single byte, the GPIO button data
    copy_to_user(buff, &button_data, 1);

    return 1;
}

static int __init gamepad_init(void)
{
    int err;
    struct device *dev;

    // allocate character device with dynamic major number and one minor number
    err = alloc_chrdev_region(&device_number, 0, NUM_MINOR, DEVICE_NAME);
    if (err < 0)
        return err;

    // init cdev
    cdev_init(&char_device, &fops);

    err = cdev_add(&char_device, device_number, NUM_MINOR);
    if (err < 0)
        return err;

    // create device file
    cl = class_create(THIS_MODULE, DEVICE_NAME);
    dev = device_create(cl, NULL, device_number, NULL, DEVICE_NAME);
    if (IS_ERR(dev))
        return PTR_ERR(dev);

    // initialize GPIO
    err = gpio_init();
    if (err < 0)
        return err;

    printk("Gamepad init success\n");

    return 0;
}

static void __exit gamepad_exit(void)
{
    // unregister, delete and destroy everything
    unregister_chrdev_region(device_number, NUM_MINOR);
    cdev_del(&char_device);
    device_destroy(cl, device_number);
    class_destroy(cl);
    gpio_exit();

    printk("Short life for a small module...\n");
}

module_init(gamepad_init);
module_exit(gamepad_exit);
MODULE_DESCRIPTION("TDT4258 Gamepad driver");
MODULE_LICENSE("GPL");

