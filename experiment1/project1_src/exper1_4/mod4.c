//<module4.c>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/jiffies.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#define BUFF_SIZE 1024

static char *str = NULL;
static struct proc_dir_entry *file = NULL;
static struct proc_dir_entry *director = NULL;

static int hello_proc_show(struct seq_file *m, void *v)
{
    /* 这里不能使用printfk之类的函数，要使用seq_file输出的一组特殊函数 */
    seq_printf(m, "str is %s\n", str);

    //必须返回0，否则什么也显示不出来
    return 0;
}

static int hello_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, hello_proc_show, NULL);
    //定义文件操作
}

static ssize_t
hello_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *f_pos)
//buffer表示要写入的缓冲区，count表示要写入的信息长度,f_pos为当前的偏移位置，这个值通常是用来判断写文件是否越界
//如果返回值非负, 则代表成功写的字节数。如果写入失败，则返回-EFAULT
{
    char *tmp = kzalloc((count + 1), GFP_KERNEL);
    size_t len = count > BUFF_SIZE?BUFF_SIZE:count;
    if (!tmp)
        return -ENOMEM;
    if (copy_from_user(tmp, buffer, len))
    {
        kfree(tmp);
        return -EFAULT;
    }
    if (str)
        kfree(str);
    str = tmp;
    return len;
}

const struct proc_ops hello_proc_fops = {
    // .owner = THIS_MODULE,
    .proc_open = hello_proc_open,
    .proc_release = single_release,
    .proc_lseek = seq_lseek,
    .proc_read_iter = seq_read_iter,
    .proc_write = hello_proc_write,
    //TODO: 指定文件操作
};

static int __init hello_proc_init(void)
{
    director = proc_mkdir("hello_dir", NULL);
    file = proc_create("hello", 0777, director, &hello_proc_fops);
    printk(KERN_INFO "/proc/hello_dir/hello has been created!\n");
    return 0;
    //TODO: 加载模块时printk输出信息
}
static void __exit hello_proc_exit(void)
{
    proc_remove(file);
    proc_remove(director);
    printk(KERN_INFO "Module4 is REMOVED!\n");
    //TODO: 卸载模块时printk输出信息，删除创建的proc文件
}
module_init(hello_proc_init);
module_exit(hello_proc_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("xianghui");
MODULE_DESCRIPTION("EXPERIMENT 4");