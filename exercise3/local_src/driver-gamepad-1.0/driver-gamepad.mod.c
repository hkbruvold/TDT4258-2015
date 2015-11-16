#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x9e6cd765, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x5e6a393d, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0xbcbe42c9, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0x4f8b5ddb, __VMLINUX_SYMBOL_STR(_copy_to_user) },
	{ 0x42c8de35, __VMLINUX_SYMBOL_STR(ioremap_nocache) },
	{ 0x1fedf0f4, __VMLINUX_SYMBOL_STR(__request_region) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x525d9634, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0xae1d4c3b, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0xb7d03be9, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0x593794fc, __VMLINUX_SYMBOL_STR(cdev_init) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
	{ 0x29b6aff0, __VMLINUX_SYMBOL_STR(platform_get_irq) },
	{ 0x2072ee9b, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0x7cd81f64, __VMLINUX_SYMBOL_STR(kill_fasync) },
	{ 0xe484e35f, __VMLINUX_SYMBOL_STR(ioread32) },
	{ 0xf10de535, __VMLINUX_SYMBOL_STR(ioread8) },
	{ 0xf20dabd8, __VMLINUX_SYMBOL_STR(free_irq) },
	{ 0x436c2179, __VMLINUX_SYMBOL_STR(iowrite32) },
	{ 0xf3fa08b, __VMLINUX_SYMBOL_STR(fasync_helper) },
	{ 0x8a86f94, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0x956e0c05, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0x52d570a7, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0x7c61340c, __VMLINUX_SYMBOL_STR(__release_region) },
	{ 0x69a358a6, __VMLINUX_SYMBOL_STR(iomem_resource) },
	{ 0xedc03953, __VMLINUX_SYMBOL_STR(iounmap) },
	{ 0x815acefd, __VMLINUX_SYMBOL_STR(platform_get_resource) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("of:N*T*Ctdt4258*");
