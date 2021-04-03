//<module2.c> //Support for int&str&array parameter
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>

static int int_var;
module_param(int_var, int, 0644); //权限是当前用户可读可写，其它用户可读
static char *str_var;
module_param(str_var, charp, 0644);
static int int_array[100];
static int num;
module_param_array(int_array, int, &num, 0644);
int i = 0;
static int __init hello_init(void)
{
    printk(KERN_INFO "Module2 is READY\n");
    printk(KERN_INFO "Parameter int_var=%d\n", int_var);
    printk(KERN_INFO "Parameter str_var=%s\n", str_var);
    for (; i < num; ++i)
    {
        printk(KERN_INFO "Parameter int_array[%d]=%d\n", i, int_array[i]);
    }
    return 0;
}
static void __exit hello_exit(void)
{
    printk(KERN_INFO "Module2 is REMOVED!\n");
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("xianghui");
MODULE_DESCRIPTION("EXPERIMENT 2");