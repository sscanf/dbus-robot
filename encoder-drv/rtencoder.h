#ifndef __MOTORES__
#define __MOTORES__

#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/proc_fs.h>

#define ENCODER_RIGHT 0
#define ENCODER_LEFT  1

#define ATRAS         0
#define ADELANTE      1
#define TOTAL_MOTORES 2
#define TOTAL_SAMPLES 1
#define TOTAL_ERRORS  3
#define LIMIT         10

#define MOD_NAME                "rtencoder"
#define STR_MODNAME             "rtencoder: "
#define TIMEOUT                 1000 // milliseconds
#define PIN_ENCODER_RIGHT_CHANA 492  // "MXM3_5"   GPIO 3
#define PIN_ENCODER_RIGHT_CHANB 493  // "MXM3_7"   GPIO 4
#define PIN_ENCODER_LEFT_CHANA  353  // "MXM3_11"  GPIO 5
#define PIN_ENCODER_LEFT_CHANB  354  // "MXM3_13"  GPIO 6

static int ModMajor;
// static u8 *ModLomem;

static struct class          *pClass;
static struct timer_list      ro_timer;
static void                   rtencoder_exit_module(void);
static struct proc_dir_entry *proc_encoder_right;
static struct proc_dir_entry *proc_encoder_left;

MODULE_DESCRIPTION("Robot rotary encoder driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Oscar Casamitjana ocasamitjana@icloud.com");

#define PROCFS_ENCODER_R_NAME "driver/robot_encoder_right"
#define PROCFS_ENCODER_L_NAME "driver/robot_encoder_left"

static const int enc_states[] = {-1, 1};

typedef struct encoder_t {
    int nPulses;
    int speed;
} encoder;

static encoder *pEncoderRight;
static encoder *pEncoderLeft;
static int initializeEncoders(void);

#endif // __MOTORES__

/*
      // **** ENCODER 1 *****

      if (MOTOR1_CHANA)
            width1++;
      else
{
         if (MOTOR1_CHANB)
            encoder[0].pulseDir=0;
         else
            encoder[0].pulseDir=1;

         if (width1)
{
            encoder[0].pulseWidth=width1;
            width1=0;
}
}


      // **** ENCODER 2 ****
         if (MOTOR2_CHANA)
            width2++;
         else
{
            if (MOTOR2_CHANB)
               encoder[1].pulseDir=0;
            else
               encoder[1].pulseDir=1;

            if (width2)
{
               encoder[1].pulseWidth=width2;
               width2=0;
}
}
*/
