#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

static dev_t chrdev;

#define NUM_MINOR (0)
#define CHRDEV_NAME ("gamepad")

static int gamepad_open(struct inode *inode, struct file *filp)
{
    return 0;
}

static int gamepad_release(struct inode *inode, struct file *filp)
{
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
    return 0;
}

static ssize_t gamepad_write(struct file *filp, const char __user *buff,
                             size_t count, loff_t *offp)
{
    return 0;
}

static int __init gamepad_init(void)
{
    printk("Hello World, here is your module speaking\n");

    // allocate character device with dynamic major number
    int err = alloc_chrdev_region(&chrdev, 0, NUM_MINOR, CHRDEV_NAME);
    if (err < 0)
        printk("Failed to allocate character device (error %d)\n", err);
    else
        printk("Major number %d, minor number %d\n",
                MAJOR(chrdev), MINOR(chrdev));

    return 0;
}

static void __exit gamepad_cleanup(void)
{
    printk("Unregistering chrdev major number %d, minor number %d\n",
            MAJOR(chrdev), MINOR(chrdev));

    // TODO: this doesn't seem to work
    unregister_chrdev_region(chrdev, NUM_MINOR);

    printk("Short life for a small module...\n");
}

module_init(gamepad_init);
module_exit(gamepad_cleanup);

MODULE_DESCRIPTION("TDT4258 Gamepad driver");
MODULE_LICENSE("GPL");

