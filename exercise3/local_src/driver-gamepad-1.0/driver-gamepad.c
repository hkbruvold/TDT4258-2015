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
static int __init gpio_init(void);
static void __exit gpio_exit(void);
static int __init gamepad_init(void);
static void __exit gamepad_exit(void);

/* file operations struct */
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = gamepad_open,
    .release = gamepad_release,
    .read = gamepad_read,
};

static int __init gpio_init(void)
{
    // request exclusive access to the GPIO port C memory region
    if (request_mem_region(GPIO_PC_BASE, GPIO_PC_LENGTH, DEVICE_NAME) == NULL)
        return -EBUSY; // "device or resource busy"

    // set pins to input with filter
    iowrite32(0x33333333, GPIO_PC_MODEL);

    // set pins to be pull-up
    iowrite32(0xff, GPIO_PC_DOUT);

    return 0;
}

static void __exit gpio_exit(void)
{
    release_mem_region(GPIO_PC_BASE, GPIO_PC_LENGTH);
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

    err = gpio_init();
    if (err < 0)
        return err;

    printk("Gamepad init success");

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

