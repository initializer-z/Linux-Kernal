//<module3.c>
//read-only proc file
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/jiffies.h>
#include <linux/slab.h>

static struct proc_dir_entry *file = NULL;

static int hello_proc_show(struct seq_file *m, void *v)
{
    /* 这里不能使用printfk之类的函数，要使用seq_file输出的一组特殊函数 */
    seq_printf(m, "This is a proc message!\n");

    //必须返回0，否则什么也显示不出来
    return 0;
}

static int hello_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, hello_proc_show, NULL);
    //定义文件操作
}

const struct proc_ops hello_proc_fops = {
    // .owner = THIS_MODULE,
    .proc_open = hello_proc_open,
    .proc_release = single_release,
    .proc_read_iter = seq_read_iter,
    .proc_lseek = seq_lseek,
    //TODO: 指定文件操作
};
static int __init hello_proc_init(void)
{

    file = proc_create("hello_proc", 0400, NULL, &hello_proc_fops);
    printk(KERN_INFO "/proc/hello_proc has been created!\n");
    return 0;
    //TODO: 加载模块时printk输出信息
}
static void __exit hello_proc_exit(void)
{
    proc_remove(file);
    printk(KERN_INFO "Module3 is REMOVED!\n");
    //TODO: 卸载模块时printk输出信息，删除创建的proc文件
}
module_init(hello_proc_init);
module_exit(hello_proc_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("xianghui");
MODULE_DESCRIPTION("EXPERIMENT 3");