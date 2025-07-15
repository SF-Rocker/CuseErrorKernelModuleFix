#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>

static dev_t dev_number;
static struct cdev my_cdev;
#include <linux/uaccess.h> // for copy_from_user, copy_to_user

#define BUF_LEN 128
static char kernel_buffer[BUF_LEN];

// read() handler
static ssize_t my_read(struct file *file, char __user *buf, size_t len, loff_t *offset)
{
    return simple_read_from_buffer(buf, len, offset, kernel_buffer, BUF_LEN);
}

// write() handler
static ssize_t my_write(struct file *file, const char __user *buf, size_t len, loff_t *offset)
{
    return simple_write_to_buffer(kernel_buffer, BUF_LEN, offset, buf, len);
}

    static int my_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "my_cuse_device opened\n");
    return 0;
}


// file operations struct
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .read = my_read,
    .write = my_write,
};



static int __init my_module_init(void)
{
    int result;

    // Allocate a device number dynamically
    result = alloc_chrdev_region(&dev_number, 0, 1, "my_cuse_device");
    if (result < 0) {
        printk(KERN_ERR "Failed to allocate char device region\n");
        return result;
    }




    // Initialize and add the character device
   cdev_init(&my_cdev, &fops);
    result = cdev_add(&my_cdev, dev_number, 1);
    if (result < 0) {
        printk(KERN_ERR "Failed to add char device\n");
        unregister_chrdev_region(dev_number, 1);
        return result;
    }

    printk(KERN_INFO "Allocated Major: %d, Minor: %d\n", MAJOR(dev_number), MINOR(dev_number));
    return 0;
}

static void __exit my_module_exit(void)
{
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev_number, 1);
    printk(KERN_INFO "Device unregistered\n");
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("You");
MODULE_DESCRIPTION("Simple CUSE character device with dynamic major number");

