#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#include "efm32gg.h"

#define NUM_MINOR (1)
#define DEVICE_NAME ("gamepad")

static dev_t device_number;
static struct cdev char_device;
struct class *cl;

/* declare functions */
static int gamepad_open(struct inode *inode, struct file *filp);
static int gamepad_release(struct inode *inode, struct file *filp);
static ssize_t gamepad_read(struct file *filp, char __user *buff,
                            size_t count, loff_t *offp);
static void __init gpio_init(void);
static int __init gamepad_init(void);
static void __exit gamepad_cleanup(void);

/* file operations struct */
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = gamepad_open,
    .release = gamepad_release,
    .read = gamepad_read,
};

// __init tells the compiler that the function is only used during init, and
// frees the function memory when the module is loaded
static void __init gpio_init(void)
{
    // initialise GPIO
    *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_GPIO; // enable GPIO clock

    *GPIO_PC_MODEL = 0x33333333; // set pins to input with filter
    *GPIO_PC_DOUT |= 0xFF; // set pin to be pull-up
}

static int gamepad_open(struct inode *inode, struct file *filp)
{
    // TODO: enable GPIO interrupts
    printk("Gamepad open\n");
    return 0;
}

static int gamepad_release(struct inode *inode, struct file *filp)
{
    // TODO: turn off interrupts for GPIO
    printk("Gamepad close\n");
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
    // user tries to read count bytes at offset from filp to buff

    char data = ioread8((void *)GPIO_PC_DIN);

    copy_to_user(buff, &data, 1);

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

    gpio_init();

    return 0;
}

static void __exit gamepad_cleanup(void)
{
    // unregister, delete and destroy everything
    unregister_chrdev_region(device_number, NUM_MINOR);
    cdev_del(&char_device);
    device_destroy(cl, device_number);
    class_destroy(cl);

    printk("Short life for a small module...\n");
}

module_init(gamepad_init);
module_exit(gamepad_cleanup);
MODULE_DESCRIPTION("TDT4258 Gamepad driver");
MODULE_LICENSE("GPL");

