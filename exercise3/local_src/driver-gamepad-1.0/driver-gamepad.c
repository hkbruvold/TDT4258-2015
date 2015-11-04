#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uacccess.h>

static dev_t device;
static struct cdev *char_device;

static char gpio_buffer[256];
static uint16_t gpio_buffer_pos;

static struct file_operations fops = {
       owner: THIS_MODULE,
       open: gamepad_open,
       release: gamepad_release
       read: gamepad_read,
       write: gamepad_write,
};

#define NUM_MINOR (1)
#define CHRDEV_NAME ("gamepad")

static int gamepad_open(struct inode *inode, struct file *filp)
{
    // TODO: initialize interrupts for GPIO
    return 0;
}

static int gamepad_release(struct inode *inode, struct file *filp)
{
    // TODO: turn off interrupts for GPIO
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

    uint32_t data = ioread32(GPIO_PC_DIN);
    copy_to_user(buff, &data, 1);
    return 1;
}

static ssize_t gamepad_write(struct file *filp, const char __user *buff,
                             size_t count, loff_t *offp)
{
    //dont neeed
    return 0;
}

static int __init gamepad_init(void)
{
    printk("Hello World, here is your module speaking\n");

    // allocate character device with dynamic major number and one minor number
    int err = alloc_chrdev_region(&device, 0, NUM_MINOR, CHRDEV_NAME);
    if (err < 0)
        printk("Failed to allocate character device (error %d)\n", err);
    else
        printk("Allocated device with major number %d, minor number %d\n",
                MAJOR(device), MINOR(device));

    //init cdev
    cdev_init(&device, &fops);
    //@Håvard: cdev_alloc is old, init is new and described in compendium 
    // create cdev struct
    //char_device = cdev_alloc();
    //char_device->owner = THIS_MODULE;
    // cdev->ops = &fops;

    err = cdev_add(char_device, device, NUM_MINOR);
    if (err < 0)
        printk("Failed to add cdev\n");

    return 0;
}

static void __exit gamepad_cleanup(void)
{
    printk("Unregistering device with major number %d, minor number %d\n",
            MAJOR(device), MINOR(device));

    unregister_chrdev_region(device, NUM_MINOR);
    cdev_del(char_device);

    printk("Short life for a small module...\n");
}

//create device file
cl = class_create(THIS_MODULE, "gamepad-class")
device_create(cl,NULL, device,NULL, "gamepad-class")

module_init(gamepad_init);
module_exit(gamepad_cleanup);

MODULE_DESCRIPTION("TDT4258 Gamepad driver");
MODULE_LICENSE("GPL");

