#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
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
	{ 0x53eda548, "module_layout" },
	{ 0x5e7fd173, "param_get_int" },
	{ 0x13095525, "param_ops_uint" },
	{ 0x677bb305, "param_ops_bool" },
	{ 0xaee86afa, "misc_register" },
	{ 0xf7123960, "proc_mkdir" },
	{ 0xa50e7d15, "fput" },
	{ 0x98140b8f, "fget" },
	{ 0x6d334118, "__get_user_8" },
	{ 0x6729d3df, "__get_user_4" },
	{ 0xf45bcf5b, "__lock_task_sighand" },
	{ 0x479c3c86, "find_next_zero_bit" },
	{ 0x8b0e7646, "expand_files" },
	{ 0x88941a06, "_raw_spin_unlock_irqrestore" },
	{ 0xfcdb78c5, "get_files_struct" },
	{ 0x21e144ed, "get_vm_area" },
	{ 0xe174aa7, "__init_waitqueue_head" },
	{ 0x33e4cbc6, "kmem_cache_alloc_trace" },
	{ 0xba66affe, "kmalloc_caches" },
	{ 0xa37d4e55, "filp_close" },
	{ 0xb85f3bbe, "pv_lock_ops" },
	{ 0x6443d74d, "_raw_spin_lock" },
	{ 0xac14bb42, "abort_exclusive_wait" },
	{ 0x4f8b5ddb, "_copy_to_user" },
	{ 0xfe50be98, "task_tgid_nr_ns" },
	{ 0x7a1e26dd, "task_nice" },
	{ 0xb8e7ce2c, "__put_user_8" },
	{ 0x12360b79, "prepare_to_wait_exclusive" },
	{ 0x1000e51, "schedule" },
	{ 0xb00ccc33, "finish_wait" },
	{ 0xe75663a, "prepare_to_wait" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0xb2fd5ceb, "__put_user_4" },
	{ 0x4f6b400b, "_copy_from_user" },
	{ 0x5a34a45c, "__kmalloc" },
	{ 0xad8d2c5b, "create_proc_entry" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0x4313c455, "set_user_nice" },
	{ 0x1118c714, "can_nice" },
	{ 0xf526695f, "current_task" },
	{ 0x6b2dc060, "dump_stack" },
	{ 0xd456ac11, "__put_task_struct" },
	{ 0x999e8297, "vfree" },
	{ 0x75313563, "put_files_struct" },
	{ 0xa6dcc773, "rb_insert_color" },
	{ 0x107deed1, "__free_pages" },
	{ 0x997c4347, "unmap_kernel_range" },
	{ 0x5e3b19c9, "zap_page_range" },
	{ 0x1436917d, "down_write" },
	{ 0x593166cc, "get_task_mm" },
	{ 0x4707f9bf, "mmput" },
	{ 0x420a6ab8, "up_write" },
	{ 0x1211455a, "vm_insert_page" },
	{ 0x4d2f393d, "map_vm_area" },
	{ 0xe59ada41, "alloc_pages_current" },
	{ 0xbdf5c25c, "rb_next" },
	{ 0xfbe27a1c, "rb_first" },
	{ 0xc0580937, "rb_erase" },
	{ 0x37a0cba, "kfree" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xa899f75f, "remove_proc_entry" },
	{ 0xf89843f9, "schedule_work" },
	{ 0x798ade4a, "mutex_unlock" },
	{ 0xd728ebf2, "mutex_lock" },
	{ 0x9edbecae, "snprintf" },
	{ 0x27e1a049, "printk" },
	{ 0xf09c7f68, "__wake_up" },
	{ 0x48917543, "param_set_int" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "CAA30BF9AB6D83B1BC76186");
