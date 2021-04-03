//<module1.c> //Test for installing and removing of module.
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
static int __init hello_init(void)
{
    printk(KERN_INFO "Module1 is READY!\n"); //输出为INFO级别，第6级
    // printk(KERN_EMERG "EMERGE -- Module1 is READY!\n"); //输出为EMERG级别，第0级
    return 0;
    //TODO: 加载模块时printk输出信息
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "Module1 is REMOVED!\n");
    //TODO: 卸载模块时printk输出信息
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("xianghui");
MODULE_DESCRIPTION("EXPERIMENT 1");
