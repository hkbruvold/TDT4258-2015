/*
 * This is a demo Linux kernel module.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

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

/*
 * template_init - function to insert this module into kernel space
 *
 * This is the first of two exported functions to handle inserting this
 * code into a running kernel
 *
 * Returns 0 if successfull, otherwise -1
 */

static int __init gamepad_init(void)
{
    printk("Hello World, here is your module speaking\n");
    return 0;
}

/*
 * template_cleanup - function to cleanup this module from kernel space
 *
 * This is the second of two exported functions to handle cleanup this
 * code from a running kernel
 */

static void __exit gamepad_cleanup(void)
{
    printk("Short life for a small module...\n");
}

module_init(gamepad_init);
module_exit(gamepad_cleanup);

MODULE_DESCRIPTION("TDT4258 Gamepad driver");
MODULE_LICENSE("GPL");

