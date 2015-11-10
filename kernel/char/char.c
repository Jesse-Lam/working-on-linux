#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define  DEVICE_NAME "testchar"
#define  CLASS_NAME  "char"

static int    majorNumber;
static char   message[256] = {0};
static short  size_of_message;
static struct class*  charClass  = NULL;
static struct device* charDevice = NULL;

static int     char_open(struct inode *, struct file *);
static int     char_release(struct inode *, struct file *);
static ssize_t char_read(struct file *, char *, size_t, loff_t *);
static ssize_t char_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops =
{
   .open = char_open,
   .read = char_read,
   .write = char_write,
   .release = char_release,
};

static int __init char_init(void){
   printk(KERN_INFO "char: Initializing the char\n");

   majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
   if (majorNumber<0){
      printk(KERN_ALERT "char failed to register a major number\n");
      return majorNumber;
   }
   printk(KERN_INFO "char: registered correctly with major number %d\n", majorNumber);

   // Register the device class
   charClass = class_create(THIS_MODULE, CLASS_NAME);
   if (IS_ERR(charClass)){
      unregister_chrdev(majorNumber, DEVICE_NAME);
      printk(KERN_ALERT "Failed to register device class\n");
      return PTR_ERR(charClass);
   }
   printk(KERN_INFO "char: device class registered correctly\n");

   // Register the device driver
   charDevice = device_create(charClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
   if (IS_ERR(charDevice)){
      class_destroy(charClass);
      unregister_chrdev(majorNumber, DEVICE_NAME);
      printk(KERN_ALERT "Failed to create the device\n");
      return PTR_ERR(charDevice);
   }
   printk(KERN_INFO "char: device class created correctly\n");
   return 0;
}

static void __exit char_exit(void){
   device_destroy(charClass, MKDEV(majorNumber, 0));     // remove the device
   class_unregister(charClass);                          // unregister the device class
   class_destroy(charClass);                             // remove the device class
   unregister_chrdev(majorNumber, DEVICE_NAME);             // unregister the major number
   printk(KERN_INFO "char: Goodbye!\n");
}

static int char_open(struct inode *inodep, struct file *filep){
   printk(KERN_INFO "char: Device open!\n");
   return 0;
}

static ssize_t char_read(struct file *filep, char *buffer, size_t len, loff_t *offset){
   copy_to_user(buffer, message, size_of_message);

   printk(KERN_INFO "char: Sent %d characters to the user\n", size_of_message);
   return (size_of_message=0);  // clear the position to the start and return 0
}

static ssize_t char_write(struct file *filep, const char *buffer, size_t len, loff_t *offset){
   sprintf(message, "%s", buffer);   // appending received string with its length
   size_of_message = strlen(message);                 // store the length of the stored message
   printk(KERN_INFO "char: Received %d characters from the user\n", len);
   return len;
}

static int char_release(struct inode *inodep, struct file *filep){
   printk(KERN_INFO "char: Device successfully closed\n");
   return 0;
}

module_init(char_init);
module_exit(char_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jake");
MODULE_DESCRIPTION("A simple Linux char driver");
MODULE_VERSION("0.1");

