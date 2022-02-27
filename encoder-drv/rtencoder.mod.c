#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0x365eea0a, "module_layout" },
	{ 0x879c176a, "kmem_cache_alloc" },
	{ 0xd24bb5a0, "kmalloc_caches" },
	{ 0x92d5838e, "request_threaded_irq" },
	{ 0x2876c77f, "gpiod_direction_input" },
	{ 0xc6f46339, "init_timer_key" },
	{ 0xb643d6ec, "device_create" },
	{ 0x5c2f35c5, "__class_create" },
	{ 0xe76ab4f8, "proc_create" },
	{ 0x37a0cba, "kfree" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x70094f3, "remove_proc_entry" },
	{ 0xca55111a, "class_destroy" },
	{ 0xa6aa210f, "device_destroy" },
	{ 0x2b68bd2f, "del_timer" },
	{ 0xc1514a3b, "free_irq" },
	{ 0xb26258cb, "gpiod_to_irq" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0x6cbbfc54, "__arch_copy_to_user" },
	{ 0x98cf60b3, "strlen" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0xfe990052, "gpio_free" },
	{ 0xd91cf7c1, "gpiod_unexport" },
	{ 0xc5850110, "printk" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x500fe3e5, "gpiod_get_raw_value" },
	{ 0xb6e368ee, "gpio_to_desc" },
	{ 0xc38c83b8, "mod_timer" },
	{ 0x15ba50a6, "jiffies" },
};

MODULE_INFO(depends, "");

