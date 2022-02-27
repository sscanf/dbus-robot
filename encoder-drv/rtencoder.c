#include "rtencoder.h"

// https://embetronicx.com/tutorials/linux/device-drivers/gpio-driver-basic-using-raspberry-pi/

static ssize_t proc_encoder_right_read(struct file *filp, char *buffer, size_t len, loff_t *offset) {
    char buf[950];
    int  ret;
    int  faltan   = 0;
    int  to_write = 0;

    ret += sprintf(buf, "%3d\n", pEncoderRight->speed);
    to_write = strlen(buf) + 1 - *offset;
    faltan   = raw_copy_to_user(buffer, buf + *offset, to_write);
    *offset += to_write - faltan;
    return to_write - faltan;
}

static ssize_t proc_encoder_left_read(struct file *filp, char *buffer, size_t len, loff_t *offset) {
    char buf[950];
    int  ret;
    int  faltan   = 0;
    int  to_write = 0;

    ret += sprintf(buf, "%3d\n", pEncoderLeft->speed);
    to_write = strlen(buf) + 1 - *offset;
    faltan   = raw_copy_to_user(buffer, buf + *offset, to_write);
    *offset += to_write - faltan;
    return to_write - faltan;
}

/*             ___     ___
 * chan A  ___|   |___|   |___      <-- Dir: 1 = Forward / 0 = Back
 *               ___     ___
 * chan B  _____|   |___|   |___    <-- Interrupt on rising edge
 *
 */
static irqreturn_t irq_encoder_right_chanb(int irq, void *dev_id) {
    int dir;
    dir = gpio_get_value(PIN_ENCODER_RIGHT_CHANA);
    pEncoderRight->nPulses += enc_states[dir];
    return IRQ_HANDLED;
}

static irqreturn_t irq_encoder_left_chanb(int irq, void *dev_id) {
    int dir;
    dir = gpio_get_value(PIN_ENCODER_LEFT_CHANA);
    pEncoderLeft->nPulses += enc_states[dir];
    return IRQ_HANDLED;
}

void resetTimer(void) {
    mod_timer(&ro_timer, jiffies + msecs_to_jiffies(TIMEOUT));
}

void timer_callback(struct timer_list *data) {
    pEncoderRight->speed   = pEncoderRight->nPulses;
    pEncoderLeft->speed    = pEncoderLeft->nPulses;
    pEncoderRight->nPulses = 0;
    pEncoderLeft->nPulses  = 0;
    resetTimer();
}

static int gpioEnablePin(int number, const char *label) {
    if (gpio_is_valid(number) == false) {
        pr_err("GPIO %d is not valid\n", number);
        return false;
    }

    if (gpio_request(number, label) < 0) {
        pr_err("ERROR: GPIO %s request\n", label);
        return false;
    }
    return true;
}

static void gpioDisablePin(int number) {
    gpio_unexport(number);
    gpio_free(number);
}

static struct file_operations encoder_right_fops = {
    .owner = THIS_MODULE,
    .read  = proc_encoder_right_read,
};

static struct file_operations encoder_left_fops= {
    .owner = THIS_MODULE,
    .read  = proc_encoder_left_read,
};

static int initializeEncoders(void) {
    int err;
    gpioEnablePin(PIN_ENCODER_RIGHT_CHANA, "ENCODER_RIGHT_CHANA");
    gpioEnablePin(PIN_ENCODER_RIGHT_CHANB, "ENCODER_RIGHT_CHANB");
    gpioEnablePin(PIN_ENCODER_LEFT_CHANA, "ENCODER_LEFT_CHANA");
    gpioEnablePin(PIN_ENCODER_LEFT_CHANB, "ENCODER_LEFT_CHANB");

    gpio_direction_input(PIN_ENCODER_RIGHT_CHANA);
    gpio_direction_input(PIN_ENCODER_RIGHT_CHANB);
    gpio_direction_input(PIN_ENCODER_LEFT_CHANA);
    gpio_direction_input(PIN_ENCODER_LEFT_CHANB);

    if ((err = request_irq(gpio_to_irq(PIN_ENCODER_RIGHT_CHANB), //
                           irq_encoder_right_chanb,
                           IRQF_SHARED | IRQF_TRIGGER_RISING,
                           "ENCODER_RIGHT_CHANB",
                           THIS_MODULE->name))
        != 0) {
        printk(KERN_INFO "Error %d: could not request irq: %d\n", err, PIN_ENCODER_RIGHT_CHANB);
    }

    if ((err = request_irq(gpio_to_irq(PIN_ENCODER_LEFT_CHANB), //
                           irq_encoder_left_chanb,
                           IRQF_SHARED | IRQF_TRIGGER_RISING,
                           "ENCODER_LEFT_CHANB",
                           THIS_MODULE->name))
        != 0) {
        printk(KERN_INFO "Error %d: could not request irq: %d\n", err, PIN_ENCODER_LEFT_CHANB);
    }

    pEncoderRight = (encoder *)kmalloc(sizeof(encoder), GFP_ATOMIC);
    memset(pEncoderRight, 0, sizeof(encoder));

    pEncoderLeft = (encoder *)kmalloc(sizeof(encoder), GFP_ATOMIC);
    memset(pEncoderLeft, 0, sizeof(encoder));
    return true;
}

static int rtencoder_init_module(void) {
    int ret;
    printk("Instaling module\n");

    proc_encoder_right = proc_create(PROCFS_ENCODER_R_NAME, 0644, NULL, &encoder_right_fops);
    if (!proc_encoder_right)
        printk(KERN_WARNING STR_MODNAME "Couldn't create /proc/%s\n", PROCFS_ENCODER_R_NAME);

    proc_encoder_left = proc_create(PROCFS_ENCODER_L_NAME, 0644, NULL, &encoder_left_fops);
    if (!proc_encoder_left)
        printk(KERN_WARNING STR_MODNAME "Couldn't create /proc/%s\n", PROCFS_ENCODER_L_NAME);

    pClass = class_create(THIS_MODULE, MOD_NAME);
    if (IS_ERR(pClass)) {
        printk(KERN_ERR STR_MODNAME "Error creating class\n");
        return -ENODEV;
    }
    device_create(pClass, NULL, MKDEV(ModMajor, 0), NULL, MOD_NAME);

    timer_setup(&ro_timer, timer_callback, 0);
    resetTimer();

    ret = initializeEncoders();
    if (!ret) {
        rtencoder_exit_module();
        return -1;
    }
    return false;
}

//---------------------------------------------------------------------------------------
//
static void rtencoder_exit_module(void) {
    free_irq(gpio_to_irq(PIN_ENCODER_RIGHT_CHANB), THIS_MODULE->name);
    free_irq(gpio_to_irq(PIN_ENCODER_LEFT_CHANB), THIS_MODULE->name);
    gpioDisablePin(PIN_ENCODER_RIGHT_CHANA);
    gpioDisablePin(PIN_ENCODER_RIGHT_CHANB);
    gpioDisablePin(PIN_ENCODER_LEFT_CHANA);
    gpioDisablePin(PIN_ENCODER_LEFT_CHANB);

    del_timer(&ro_timer);
    device_destroy(pClass, MKDEV(ModMajor, 0));
    class_destroy(pClass);
    remove_proc_entry(PROCFS_ENCODER_L_NAME, NULL);
    remove_proc_entry(PROCFS_ENCODER_R_NAME, NULL);
    unregister_chrdev(ModMajor, MOD_NAME);
    printk(KERN_INFO STR_MODNAME "exit\n");

    kfree(pEncoderRight);
    kfree(pEncoderLeft);
}

module_init(rtencoder_init_module);
module_exit(rtencoder_exit_module);
