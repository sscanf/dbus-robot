#ifndef I2C_SLAVE_H_
#define I2C_SLAVE_H_

#include <pic18fregs.h>

  /* I2C modes of operation */
#define I2C_SLAVE10B_INT        0x0f
#define I2C_SLAVE7B_INT         0x0e
#define I2C_SLAVE_IDLE          0x0b
#define I2C_MASTER              0x08
#define I2C_SLAVE10B            0x07
#define I2C_SLAVE7B             0x06

  /* slew rate control */
#define I2C_SLEW_OFF    0xc0
#define I2C_SLEW_ON     0x00

  /* macros to generate hardware conditions on I2C module
     SSPIF needs to be cleared before using START/STOP/RESTART
  */

  /* wait for SSPID to occur */
#define I2C_WAIT()  while (!PIR1bits.SSPIF) ; PIR1bits.SSPIF = 0;

void i2c_open(unsigned char mode, unsigned char slew, unsigned char addr_brd);
void i2c_start(void);
void i2c_stop(void);
void i2c_restart(void);
void i2c_ack(void);
void i2c_nack(void);
void i2c_wait(void);

unsigned char i2c_readchar(void);
char i2c_readstr(unsigned char *ptr, unsigned char len);

char i2c_writechar(unsigned char dat);
char i2c_writestr(unsigned char *ptr, unsigned char len);
#endif
