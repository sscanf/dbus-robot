#ifndef __MOTORES__
#define __MOTORES__ 1


#define MOTOR_1   0
#define MOTOR_2   1

#define ATRAS		0
#define ADELANTE	1

#define TOTAL_MOTORES 	2
#define TOTAL_SAMPLES	1
#define TOTAL_ERRORS		3
#define LIMIT				10

#define MOTOR1_DIR         PORTAbits.RA1
#define MOTOR1_DIR_TRIS    TRISAbits.TRISA0
#define MOTOR1_CHANA       PORTDbits.RD3
#define MOTOR1_CHANB       PORTDbits.RD2 
#define MOTOR1_CHANA_TRIS  TRISDbits.TRISD3
#define MOTOR1_CHANB_TRIS  TRISDbits.TRISD2
#define MOTOR1_PWM         PORTCbits.RC1
#define MOTOR1_PWM_TRIS    TRISCbits.TRISC1

#define MOTOR2_DIR         PORTAbits.RA0
#define MOTOR2_DIR_TRIS    TRISAbits.TRISA1
#define MOTOR2_CHANA       PORTDbits.RD0
#define MOTOR2_CHANB       PORTDbits.RD1 
#define MOTOR2_CHANA_TRIS  TRISDbits.TRISD0
#define MOTOR2_CHANB_TRIS  TRISDbits.TRISD1
#define MOTOR2_PWM         PORTCbits.RC2
#define MOTOR2_PWM_TRIS    TRISCbits.TRISC2



void readEncoders(void);

struct encoder_t
{
   unsigned int pulseDir;
   unsigned int AntChana;
	int inSpeed;
	int outSpeed;
	int giro;
	unsigned int time_collision;
	unsigned char sentido;	//1 = adelante 0 = atras
};


void initializeMotors(void);
int getEncoderWidth(unsigned char motor);
unsigned char getEncoderDir(unsigned char motor);
int motorChangeDir (unsigned char dir, unsigned char motor);
void motorSpeed (int speed, unsigned char motor);
void setMotorsDebug (char debug);
void motorGira (int center);
void setPidEnabled (char enabled);
unsigned char motorDir (unsigned char motor);
int motorInvertDir (unsigned char motor);


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
