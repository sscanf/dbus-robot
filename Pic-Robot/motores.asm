;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.0 #8981 (Apr  5 2014) (Linux)
; This file was generated Mon Sep  1 01:28:50 2014
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------

	.ident "SDCC version 3.4.0 #8981 [pic16 port]"
	.file	"motores.c"
	list	p=18f4455
	radix	dec


;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	_bDebug
	global	_readEncoders
	global	_initializeMotors
	global	_setPidEnabled
	global	_motorSpeed
	global	_setMotorsDebug
	global	_motorDir
	global	_motorInvertDir
	global	_motorChangeDir
	global	_getEncoderWidth
	global	_getEncoderDir
	global	_current_state
	global	_TimerTimeout
	global	_abs
	global	_stSampling
	global	_stWaitForMotor1Bak
	global	_stWaitForMotor2Bak
	global	_stWaitForMotor1Forward
	global	_stWaitForMotor2Forward

;--------------------------------------------------------
; extern variables in this module
;--------------------------------------------------------
	extern	_SPPCFGbits
	extern	_SPPEPSbits
	extern	_SPPCONbits
	extern	_UFRMLbits
	extern	_UFRMHbits
	extern	_UIRbits
	extern	_UIEbits
	extern	_UEIRbits
	extern	_UEIEbits
	extern	_USTATbits
	extern	_UCONbits
	extern	_UADDRbits
	extern	_UCFGbits
	extern	_UEP0bits
	extern	_UEP1bits
	extern	_UEP2bits
	extern	_UEP3bits
	extern	_UEP4bits
	extern	_UEP5bits
	extern	_UEP6bits
	extern	_UEP7bits
	extern	_UEP8bits
	extern	_UEP9bits
	extern	_UEP10bits
	extern	_UEP11bits
	extern	_UEP12bits
	extern	_UEP13bits
	extern	_UEP14bits
	extern	_UEP15bits
	extern	_PORTAbits
	extern	_PORTBbits
	extern	_PORTCbits
	extern	_PORTDbits
	extern	_PORTEbits
	extern	_LATAbits
	extern	_LATBbits
	extern	_LATCbits
	extern	_LATDbits
	extern	_LATEbits
	extern	_DDRAbits
	extern	_TRISAbits
	extern	_DDRBbits
	extern	_TRISBbits
	extern	_DDRCbits
	extern	_TRISCbits
	extern	_DDRDbits
	extern	_TRISDbits
	extern	_DDREbits
	extern	_TRISEbits
	extern	_OSCTUNEbits
	extern	_PIE1bits
	extern	_PIR1bits
	extern	_IPR1bits
	extern	_PIE2bits
	extern	_PIR2bits
	extern	_IPR2bits
	extern	_EECON1bits
	extern	_RCSTAbits
	extern	_TXSTAbits
	extern	_T3CONbits
	extern	_CMCONbits
	extern	_CVRCONbits
	extern	_CCP1ASbits
	extern	_ECCP1ASbits
	extern	_CCP1DELbits
	extern	_ECCP1DELbits
	extern	_BAUDCONbits
	extern	_BAUDCTLbits
	extern	_CCP2CONbits
	extern	_CCP1CONbits
	extern	_ECCP1CONbits
	extern	_ADCON2bits
	extern	_ADCON1bits
	extern	_ADCON0bits
	extern	_SSPCON2bits
	extern	_SSPCON1bits
	extern	_SSPSTATbits
	extern	_T2CONbits
	extern	_T1CONbits
	extern	_RCONbits
	extern	_WDTCONbits
	extern	_HLVDCONbits
	extern	_LVDCONbits
	extern	_OSCCONbits
	extern	_T0CONbits
	extern	_STATUSbits
	extern	_INTCON3bits
	extern	_INTCON2bits
	extern	_INTCONbits
	extern	_STKPTRbits
	extern	_stdin
	extern	_stdout
	extern	_SPPDATA
	extern	_SPPCFG
	extern	_SPPEPS
	extern	_SPPCON
	extern	_UFRM
	extern	_UFRML
	extern	_UFRMH
	extern	_UIR
	extern	_UIE
	extern	_UEIR
	extern	_UEIE
	extern	_USTAT
	extern	_UCON
	extern	_UADDR
	extern	_UCFG
	extern	_UEP0
	extern	_UEP1
	extern	_UEP2
	extern	_UEP3
	extern	_UEP4
	extern	_UEP5
	extern	_UEP6
	extern	_UEP7
	extern	_UEP8
	extern	_UEP9
	extern	_UEP10
	extern	_UEP11
	extern	_UEP12
	extern	_UEP13
	extern	_UEP14
	extern	_UEP15
	extern	_PORTA
	extern	_PORTB
	extern	_PORTC
	extern	_PORTD
	extern	_PORTE
	extern	_LATA
	extern	_LATB
	extern	_LATC
	extern	_LATD
	extern	_LATE
	extern	_DDRA
	extern	_TRISA
	extern	_DDRB
	extern	_TRISB
	extern	_DDRC
	extern	_TRISC
	extern	_DDRD
	extern	_TRISD
	extern	_DDRE
	extern	_TRISE
	extern	_OSCTUNE
	extern	_PIE1
	extern	_PIR1
	extern	_IPR1
	extern	_PIE2
	extern	_PIR2
	extern	_IPR2
	extern	_EECON1
	extern	_EECON2
	extern	_EEDATA
	extern	_EEADR
	extern	_RCSTA
	extern	_TXSTA
	extern	_TXREG
	extern	_RCREG
	extern	_SPBRG
	extern	_SPBRGH
	extern	_T3CON
	extern	_TMR3
	extern	_TMR3L
	extern	_TMR3H
	extern	_CMCON
	extern	_CVRCON
	extern	_CCP1AS
	extern	_ECCP1AS
	extern	_CCP1DEL
	extern	_ECCP1DEL
	extern	_BAUDCON
	extern	_BAUDCTL
	extern	_CCP2CON
	extern	_CCPR2
	extern	_CCPR2L
	extern	_CCPR2H
	extern	_CCP1CON
	extern	_ECCP1CON
	extern	_CCPR1
	extern	_CCPR1L
	extern	_CCPR1H
	extern	_ADCON2
	extern	_ADCON1
	extern	_ADCON0
	extern	_ADRES
	extern	_ADRESL
	extern	_ADRESH
	extern	_SSPCON2
	extern	_SSPCON1
	extern	_SSPSTAT
	extern	_SSPADD
	extern	_SSPBUF
	extern	_T2CON
	extern	_PR2
	extern	_TMR2
	extern	_T1CON
	extern	_TMR1
	extern	_TMR1L
	extern	_TMR1H
	extern	_RCON
	extern	_WDTCON
	extern	_HLVDCON
	extern	_LVDCON
	extern	_OSCCON
	extern	_T0CON
	extern	_TMR0
	extern	_TMR0L
	extern	_TMR0H
	extern	_STATUS
	extern	_FSR2L
	extern	_FSR2H
	extern	_PLUSW2
	extern	_PREINC2
	extern	_POSTDEC2
	extern	_POSTINC2
	extern	_INDF2
	extern	_BSR
	extern	_FSR1L
	extern	_FSR1H
	extern	_PLUSW1
	extern	_PREINC1
	extern	_POSTDEC1
	extern	_POSTINC1
	extern	_INDF1
	extern	_WREG
	extern	_FSR0L
	extern	_FSR0H
	extern	_PLUSW0
	extern	_PREINC0
	extern	_POSTDEC0
	extern	_POSTINC0
	extern	_INDF0
	extern	_INTCON3
	extern	_INTCON2
	extern	_INTCON
	extern	_PROD
	extern	_PRODL
	extern	_PRODH
	extern	_TABLAT
	extern	_TBLPTR
	extern	_TBLPTRL
	extern	_TBLPTRH
	extern	_TBLPTRU
	extern	_PC
	extern	_PCL
	extern	_PCLATH
	extern	_PCLATU
	extern	_STKPTR
	extern	_TOS
	extern	_TOSL
	extern	_TOSH
	extern	_TOSU
	extern	_printf
	extern	_memset
	extern	__mulint
	extern	__divsint

;--------------------------------------------------------
;	Equates to used internal registers
;--------------------------------------------------------
STATUS	equ	0xfd8
PCL	equ	0xff9
PCLATH	equ	0xffa
PCLATU	equ	0xffb
INTCON	equ	0xff2
WREG	equ	0xfe8
TOSL	equ	0xffd
TOSH	equ	0xffe
TOSU	equ	0xfff
FSR0L	equ	0xfe9
FSR0H	equ	0xfea
FSR1L	equ	0xfe1
FSR2L	equ	0xfd9
INDF0	equ	0xfef
POSTINC0	equ	0xfee
POSTINC1	equ	0xfe6
POSTDEC1	equ	0xfe5
PREINC1	equ	0xfe4
PLUSW2	equ	0xfdb
PRODL	equ	0xff3
PRODH	equ	0xff4


	idata
_bDebug	db	0x01
_bPidEnabled	db	0x01
_stSampling_enc_states_1_61	db	0x00, 0x01, 0xff, 0x00, 0xff, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0xff
	db	0x00, 0xff, 0x01, 0x00
_stSampling_width1_1_61	db	0x00, 0x00
_stSampling_width2_1_61	db	0x00, 0x00
_stSampling_enc_position_a_1_61	db	0x00, 0x00
_stSampling_enc_position_b_1_61	db	0x00, 0x00
_stSampling_tiempo_1_61	db	0x00, 0x00
_stAveraged_nErrors_1_72	db	0x00, 0x00
_readEncoders_counter_1_82	db	0x00


; Internal registers
.registers	udata_ovr	0x0000
r0x00	res	1
r0x01	res	1
r0x02	res	1
r0x03	res	1
r0x04	res	1
r0x05	res	1
r0x06	res	1
r0x07	res	1
r0x08	res	1
r0x09	res	1
r0x0a	res	1
r0x0b	res	1
r0x0c	res	1
r0x0d	res	1

udata_motores_0	udata
_current_state	res	3

udata_motores_1	udata
_encoder	res	26

udata_motores_2	udata
_stAveraged_errors1_1_72	res	6

udata_motores_3	udata
_stAveraged_errors2_1_72	res	6

udata_motores_4	udata
_TimerTimeout	res	1

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; I code from now on!
; ; Starting pCode block
S_motores__getEncoderDir	code
_getEncoderDir:
	.line	354; motores.c	unsigned char getEncoderDir(unsigned char motor)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
; ;multiply lit val:0x0d by variable r0x00 and store in r0x00
	.line	356; motores.c	return encoder[motor].pulseDir;
	MOVF	r0x00, W
	MULLW	0x0d
	MOVF	PRODH, W
	MOVWF	r0x01
	MOVFF	PRODL, r0x00
	MOVLW	LOW(_encoder)
	ADDWF	r0x00, F
	MOVLW	HIGH(_encoder)
	ADDWFC	r0x01, F
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, FSR0H
	MOVFF	POSTINC0, r0x00
	MOVFF	INDF0, r0x01
	MOVF	r0x00, W
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_motores__getEncoderWidth	code
_getEncoderWidth:
	.line	349; motores.c	int getEncoderWidth(unsigned char motor)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
; ;multiply lit val:0x0d by variable r0x00 and store in r0x00
	.line	351; motores.c	return encoder[motor].inSpeed;
	MOVF	r0x00, W
	MULLW	0x0d
	MOVF	PRODH, W
	MOVWF	r0x01
	MOVFF	PRODL, r0x00
	MOVLW	LOW(_encoder)
	ADDWF	r0x00, F
	MOVLW	HIGH(_encoder)
	ADDWFC	r0x01, F
	MOVLW	0x04
	ADDWF	r0x00, F
	BTFSC	STATUS, 0
	INCF	r0x01, F
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, FSR0H
	MOVFF	POSTINC0, r0x00
	MOVFF	INDF0, r0x01
	MOVFF	r0x01, PRODL
	MOVF	r0x00, W
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_motores__motorChangeDir	code
_motorChangeDir:
	.line	327; motores.c	int motorChangeDir (unsigned char dir, unsigned char motor)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVFF	r0x05, POSTDEC1
	MOVFF	r0x06, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	.line	329; motores.c	int ret=0;
	CLRF	r0x02
	CLRF	r0x03
	.line	331; motores.c	printf ("motorChangeDir\n\r");
	MOVLW	UPPER(___str_2)
	MOVWF	r0x06
	MOVLW	HIGH(___str_2)
	MOVWF	r0x05
	MOVLW	LOW(___str_2)
	MOVWF	r0x04
	MOVF	r0x06, W
	MOVWF	POSTDEC1
	MOVF	r0x05, W
	MOVWF	POSTDEC1
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	CALL	_printf
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	332; motores.c	switch (motor)
	MOVF	r0x01, W
	BZ	_00346_DS_
	MOVF	r0x01, W
	XORLW	0x01
	BZ	_00347_DS_
	BRA	_00348_DS_
_00346_DS_:
	.line	335; motores.c	MOTOR1_DIR=!dir;
	MOVF	r0x00, W
	BSF	STATUS, 0
	TSTFSZ	WREG
	BCF	STATUS, 0
	CLRF	r0x01
	RLCF	r0x01, F
	MOVF	r0x01, W
	ANDLW	0x01
	RLNCF	WREG, W
	MOVWF	PRODH
	MOVF	_PORTAbits, W
	ANDLW	0xfd
	IORWF	PRODH, W
	MOVWF	_PORTAbits
	.line	336; motores.c	break;
	BRA	_00349_DS_
_00347_DS_:
	.line	339; motores.c	MOTOR2_DIR=dir;
	MOVF	r0x00, W
	ANDLW	0x01
	MOVWF	PRODH
	MOVF	_PORTAbits, W
	ANDLW	0xfe
	IORWF	PRODH, W
	MOVWF	_PORTAbits
	.line	340; motores.c	break;
	BRA	_00349_DS_
_00348_DS_:
	.line	343; motores.c	ret=1;
	MOVLW	0x01
	MOVWF	r0x02
	CLRF	r0x03
_00349_DS_:
	.line	346; motores.c	return ret;
	MOVFF	r0x03, PRODL
	MOVF	r0x02, W
	MOVFF	PREINC1, r0x06
	MOVFF	PREINC1, r0x05
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_motores__motorInvertDir	code
_motorInvertDir:
	.line	305; motores.c	int motorInvertDir (unsigned char motor)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVFF	r0x05, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	.line	307; motores.c	int ret=0;
	CLRF	r0x01
	CLRF	r0x02
	.line	309; motores.c	printf ("motorInvertDir\n\r");
	MOVLW	UPPER(___str_1)
	MOVWF	r0x05
	MOVLW	HIGH(___str_1)
	MOVWF	r0x04
	MOVLW	LOW(___str_1)
	MOVWF	r0x03
	MOVF	r0x05, W
	MOVWF	POSTDEC1
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	MOVF	r0x03, W
	MOVWF	POSTDEC1
	CALL	_printf
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	310; motores.c	switch (motor)
	MOVF	r0x00, W
	BZ	_00326_DS_
	MOVF	r0x00, W
	XORLW	0x01
	BZ	_00327_DS_
	BRA	_00328_DS_
_00326_DS_:
	.line	313; motores.c	MOTOR1_DIR=~MOTOR1_DIR;
	BSF	_PORTAbits, 1
	.line	314; motores.c	break;
	BRA	_00329_DS_
_00327_DS_:
	.line	317; motores.c	MOTOR2_DIR=~MOTOR2_DIR;
	BSF	_PORTAbits, 0
	.line	318; motores.c	break;
	BRA	_00329_DS_
_00328_DS_:
	.line	321; motores.c	ret=1;
	MOVLW	0x01
	MOVWF	r0x01
	CLRF	r0x02
_00329_DS_:
	.line	324; motores.c	return ret;
	MOVFF	r0x02, PRODL
	MOVF	r0x01, W
	MOVFF	PREINC1, r0x05
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_motores__motorDir	code
_motorDir:
	.line	287; motores.c	unsigned char motorDir (unsigned char motor)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	.line	289; motores.c	unsigned char ret=0;
	CLRF	r0x01
	.line	291; motores.c	switch (motor)
	MOVF	r0x00, W
	BZ	_00307_DS_
	MOVF	r0x00, W
	XORLW	0x01
	BZ	_00308_DS_
	BRA	_00309_DS_
_00307_DS_:
	.line	294; motores.c	ret=!MOTOR1_DIR;
	CLRF	r0x00
	BTFSC	_PORTAbits, 1
	INCF	r0x00, F
	MOVF	r0x00, W
	BSF	STATUS, 0
	TSTFSZ	WREG
	BCF	STATUS, 0
	CLRF	r0x01
	RLCF	r0x01, F
	.line	295; motores.c	break;
	BRA	_00309_DS_
_00308_DS_:
	.line	298; motores.c	ret=MOTOR2_DIR;
	CLRF	r0x00
	BTFSC	_PORTAbits, 0
	INCF	r0x00, F
	MOVFF	r0x00, r0x01
_00309_DS_:
	.line	302; motores.c	return ret;
	MOVF	r0x01, W
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_motores__setMotorsDebug	code
_setMotorsDebug:
	.line	282; motores.c	void setMotorsDebug (char debug)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVLW	0x02
	MOVFF	PLUSW2, _bDebug
	.line	284; motores.c	bDebug=debug;
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_motores__motorSpeed	code
_motorSpeed:
	.line	276; motores.c	void motorSpeed (int speed, unsigned char motor)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
; ;multiply lit val:0x0d by variable r0x02 and store in r0x02
	.line	279; motores.c	encoder[motor].outSpeed=(speed*2);
	MOVF	r0x02, W
	MULLW	0x0d
	MOVF	PRODH, W
	MOVWF	r0x03
	MOVFF	PRODL, r0x02
	MOVLW	LOW(_encoder)
	ADDWF	r0x02, F
	MOVLW	HIGH(_encoder)
	ADDWFC	r0x03, F
	MOVLW	0x06
	ADDWF	r0x02, F
	BTFSC	STATUS, 0
	INCF	r0x03, F
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x02
	MOVWF	POSTDEC1
	CALL	__mulint
	MOVWF	r0x00
	MOVFF	PRODL, r0x01
	MOVLW	0x04
	ADDWF	FSR1L, F
	MOVFF	r0x02, FSR0L
	MOVFF	r0x03, FSR0H
	MOVFF	r0x00, POSTINC0
	MOVFF	r0x01, INDF0
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_motores__setPidEnabled	code
_setPidEnabled:
	.line	272; motores.c	void setPidEnabled (char enabled)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVLW	0x02
	MOVFF	PLUSW2, _bPidEnabled
	.line	274; motores.c	bPidEnabled = enabled;
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_motores__initializeMotors	code
_initializeMotors:
	.line	227; motores.c	void initializeMotors(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVFF	r0x05, POSTDEC1
	.line	230; motores.c	ADCON1 |= 0x0F; // Set all I/O pins to digital
	MOVLW	0x0f
	IORWF	_ADCON1, F
	.line	231; motores.c	UCFG = 0x14; // Enable pullup resistors; full speed mode
	MOVLW	0x14
	MOVWF	_UCFG
	.line	232; motores.c	PORTEbits.RDPU=1;    //Resistencias pull-up en PORTD activas
	BSF	_PORTEbits, 7
	.line	234; motores.c	MOTOR1_DIR_TRIS=0;   //Bits de direccion motor 1 salidas
	BCF	_TRISAbits, 0
	.line	235; motores.c	MOTOR1_PWM_TRIS=0;   //Canal PWM motor 1 salidas
	BCF	_TRISCbits, 1
	.line	236; motores.c	MOTOR1_CHANA_TRIS=1;
	BSF	_TRISDbits, 3
	.line	237; motores.c	MOTOR1_CHANB_TRIS=1;
	BSF	_TRISDbits, 2
	.line	239; motores.c	MOTOR2_DIR_TRIS=0;   //Bits de direccion motor 2 salidas
	BCF	_TRISAbits, 1
	.line	240; motores.c	MOTOR2_PWM_TRIS=0;   //Canal PWM motor 2 salidas
	BCF	_TRISCbits, 2
	.line	241; motores.c	MOTOR2_CHANA_TRIS=1;
	BSF	_TRISDbits, 0
	.line	242; motores.c	MOTOR2_CHANB_TRIS=1;
	BSF	_TRISDbits, 1
	.line	252; motores.c	PR2 = BIN(01111100) ;
	MOVLW	0x7c
	MOVWF	_PR2
	.line	254; motores.c	T2CON = BIN(00000101);
	MOVLW	0x05
	MOVWF	_T2CON
	.line	255; motores.c	CCPR1L = 0;
	CLRF	_CCPR1L
	.line	256; motores.c	CCPR2L = 0;
	CLRF	_CCPR2L
	.line	257; motores.c	CCP1CON = BIN(00111100) ;
	MOVLW	0x3c
	MOVWF	_CCP1CON
	.line	258; motores.c	CCP2CON = BIN(00111100) ;
	MOVLW	0x3c
	MOVWF	_CCP2CON
	.line	260; motores.c	memset (encoder,0,sizeof (encoder)*TOTAL_MOTORES);
	MOVLW	LOW(_encoder)
	MOVWF	r0x00
	MOVLW	HIGH(_encoder)
	MOVWF	r0x01
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x34
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_memset
	MOVLW	0x05
	ADDWF	FSR1L, F
	.line	261; motores.c	TimerTimeout=1;
	MOVLW	0x01
	BANKSEL	_TimerTimeout
	MOVWF	_TimerTimeout, B
	.line	262; motores.c	encoder[MOTOR_1].AntChana=MOTOR1_CHANA;
	CLRF	r0x00
	BTFSC	_PORTDbits, 3
	INCF	r0x00, F
	CLRF	r0x01
	MOVF	r0x00, W
	BANKSEL	(_encoder + 2)
	MOVWF	(_encoder + 2), B
	MOVF	r0x01, W
	BANKSEL	(_encoder + 3)
	MOVWF	(_encoder + 3), B
	.line	263; motores.c	encoder[MOTOR_2].AntChana=MOTOR2_CHANA;
	CLRF	r0x00
	BTFSC	_PORTDbits, 0
	INCF	r0x00, F
	CLRF	r0x01
	MOVF	r0x00, W
	BANKSEL	(_encoder + 15)
	MOVWF	(_encoder + 15), B
	MOVF	r0x01, W
	BANKSEL	(_encoder + 16)
	MOVWF	(_encoder + 16), B
	.line	265; motores.c	motorChangeDir (ADELANTE,MOTOR_1);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_motorChangeDir
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	266; motores.c	motorChangeDir (ADELANTE,MOTOR_2);
	MOVLW	0x01
	MOVWF	POSTDEC1
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_motorChangeDir
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	.line	268; motores.c	current_state=&stSampling;
	MOVLW	LOW(_stSampling)
	BANKSEL	_current_state
	MOVWF	_current_state, B
	MOVLW	HIGH(_stSampling)
	BANKSEL	(_current_state + 1)
	MOVWF	(_current_state + 1), B
	MOVLW	UPPER(_stSampling)
	BANKSEL	(_current_state + 2)
	MOVWF	(_current_state + 2), B
	BANKSEL	(_current_state + 2)
	.line	269; motores.c	printf ("Initialize Motors %x\n\r",(void *)current_state);
	MOVF	(_current_state + 2), W, B
	MOVWF	r0x02
	BANKSEL	(_current_state + 1)
	MOVF	(_current_state + 1), W, B
	MOVWF	r0x01
	BANKSEL	_current_state
	MOVF	_current_state, W, B
	MOVWF	r0x00
	MOVLW	UPPER(___str_0)
	MOVWF	r0x05
	MOVLW	HIGH(___str_0)
	MOVWF	r0x04
	MOVLW	LOW(___str_0)
	MOVWF	r0x03
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	MOVF	r0x05, W
	MOVWF	POSTDEC1
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	MOVF	r0x03, W
	MOVWF	POSTDEC1
	CALL	_printf
	MOVLW	0x06
	ADDWF	FSR1L, F
	MOVFF	PREINC1, r0x05
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_motores__readEncoders	code
_readEncoders:
	.line	216; motores.c	void readEncoders(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	BANKSEL	_readEncoders_counter_1_82
	.line	220; motores.c	if (++counter>=TimerTimeout)
	INCF	_readEncoders_counter_1_82, F, B
	BANKSEL	_TimerTimeout
	MOVF	_TimerTimeout, W, B
	BANKSEL	_readEncoders_counter_1_82
	SUBWF	_readEncoders_counter_1_82, W, B
	BNC	_00276_DS_
	.line	222; motores.c	(*current_state)();
	MOVFF	INTCON, POSTDEC1
	BCF	INTCON, 7
	PUSH	
	MOVLW	LOW(_00282_DS_)
	MOVWF	TOSL
	MOVLW	HIGH(_00282_DS_)
	MOVWF	TOSH
	MOVLW	UPPER(_00282_DS_)
	MOVWF	TOSU
	BTFSC	PREINC1, 7
	BSF	INTCON, 7
	MOVFF	(_current_state + 2), PCLATU
	MOVFF	(_current_state + 1), PCLATH
	BANKSEL	_current_state
	MOVF	_current_state, W, B
	MOVWF	PCL
_00282_DS_:
	BANKSEL	_readEncoders_counter_1_82
	.line	223; motores.c	counter=0;
	CLRF	_readEncoders_counter_1_82, B
_00276_DS_:
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_motores__stAveraged	code
_stAveraged:
	.line	134; motores.c	void stAveraged(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVFF	r0x05, POSTDEC1
	MOVFF	r0x06, POSTDEC1
	MOVFF	r0x07, POSTDEC1
	MOVFF	r0x08, POSTDEC1
	MOVFF	r0x09, POSTDEC1
	MOVFF	r0x0a, POSTDEC1
	MOVFF	r0x0b, POSTDEC1
	MOVFF	r0x0c, POSTDEC1
	MOVFF	r0x0d, POSTDEC1
	.line	143; motores.c	width1=encoder[MOTOR_1].inSpeed;
	MOVFF	(_encoder + 4), r0x00
	MOVFF	(_encoder + 5), r0x01
	.line	144; motores.c	width2=encoder[MOTOR_2].inSpeed;
	MOVFF	(_encoder + 17), r0x02
	MOVFF	(_encoder + 18), r0x03
	.line	146; motores.c	outSpeed1=(encoder[MOTOR_1].outSpeed);
	MOVFF	(_encoder + 6), r0x04
	MOVFF	(_encoder + 7), r0x05
	.line	147; motores.c	outSpeed2=(encoder[MOTOR_2].outSpeed);
	MOVFF	(_encoder + 19), r0x06
	MOVFF	(_encoder + 20), r0x07
	.line	149; motores.c	if  (outSpeed1 < 0 )
	BSF	STATUS, 0
	BTFSS	r0x05, 7
	BCF	STATUS, 0
	BNC	_00166_DS_
	.line	151; motores.c	outSpeed1*=-1;
	COMF	r0x05, F
	NEGF	r0x04
	BTFSC	STATUS, 2
	INCF	r0x05, F
	.line	152; motores.c	if (motorDir(MOTOR_1)==ADELANTE)
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_motorDir
	MOVWF	r0x08
	MOVF	POSTINC1, F
	MOVF	r0x08, W
	XORLW	0x01
	BNZ	_00167_DS_
	.line	154; motores.c	CCPR1L=0;
	CLRF	_CCPR1L
	BANKSEL	_stAveraged_nErrors_1_72
	.line	155; motores.c	nErrors=0;
	CLRF	_stAveraged_nErrors_1_72, B
	BANKSEL	(_stAveraged_nErrors_1_72 + 1)
	CLRF	(_stAveraged_nErrors_1_72 + 1), B
	.line	156; motores.c	current_state=&stWaitForMotor1Bak;
	MOVLW	LOW(_stWaitForMotor1Bak)
	BANKSEL	_current_state
	MOVWF	_current_state, B
	MOVLW	HIGH(_stWaitForMotor1Bak)
	BANKSEL	(_current_state + 1)
	MOVWF	(_current_state + 1), B
	MOVLW	UPPER(_stWaitForMotor1Bak)
	BANKSEL	(_current_state + 2)
	MOVWF	(_current_state + 2), B
	.line	157; motores.c	return;
	BRA	_00191_DS_
_00166_DS_:
	.line	160; motores.c	else if (outSpeed1>0 && motorDir(MOTOR_1)==ATRAS)
	MOVF	r0x05, W
	ADDLW	0x80
	ADDLW	0x80
	BNZ	_00258_DS_
	MOVLW	0x01
	SUBWF	r0x04, W
_00258_DS_:
	BNC	_00167_DS_
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_motorDir
	MOVWF	r0x08
	MOVF	POSTINC1, F
	MOVF	r0x08, W
	BNZ	_00167_DS_
	.line	162; motores.c	CCPR1L=0;
	CLRF	_CCPR1L
	BANKSEL	_stAveraged_nErrors_1_72
	.line	163; motores.c	nErrors=0;
	CLRF	_stAveraged_nErrors_1_72, B
	BANKSEL	(_stAveraged_nErrors_1_72 + 1)
	CLRF	(_stAveraged_nErrors_1_72 + 1), B
	.line	164; motores.c	current_state=&stWaitForMotor1Forward;
	MOVLW	LOW(_stWaitForMotor1Forward)
	BANKSEL	_current_state
	MOVWF	_current_state, B
	MOVLW	HIGH(_stWaitForMotor1Forward)
	BANKSEL	(_current_state + 1)
	MOVWF	(_current_state + 1), B
	MOVLW	UPPER(_stWaitForMotor1Forward)
	BANKSEL	(_current_state + 2)
	MOVWF	(_current_state + 2), B
	.line	165; motores.c	return;
	BRA	_00191_DS_
_00167_DS_:
	.line	168; motores.c	if  (outSpeed2 < 0 )
	BSF	STATUS, 0
	BTFSS	r0x07, 7
	BCF	STATUS, 0
	BNC	_00174_DS_
	.line	170; motores.c	outSpeed2*=-1;
	COMF	r0x07, F
	NEGF	r0x06
	BTFSC	STATUS, 2
	INCF	r0x07, F
	.line	171; motores.c	if (motorDir(MOTOR_2)==ADELANTE)
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_motorDir
	MOVWF	r0x08
	MOVF	POSTINC1, F
	MOVF	r0x08, W
	XORLW	0x01
	BNZ	_00175_DS_
	.line	173; motores.c	CCPR2L=0;
	CLRF	_CCPR2L
	BANKSEL	_stAveraged_nErrors_1_72
	.line	174; motores.c	nErrors=0;
	CLRF	_stAveraged_nErrors_1_72, B
	BANKSEL	(_stAveraged_nErrors_1_72 + 1)
	CLRF	(_stAveraged_nErrors_1_72 + 1), B
	.line	175; motores.c	current_state=&stWaitForMotor2Bak;
	MOVLW	LOW(_stWaitForMotor2Bak)
	BANKSEL	_current_state
	MOVWF	_current_state, B
	MOVLW	HIGH(_stWaitForMotor2Bak)
	BANKSEL	(_current_state + 1)
	MOVWF	(_current_state + 1), B
	MOVLW	UPPER(_stWaitForMotor2Bak)
	BANKSEL	(_current_state + 2)
	MOVWF	(_current_state + 2), B
	.line	176; motores.c	return;
	BRA	_00191_DS_
_00174_DS_:
	.line	179; motores.c	else if ( outSpeed2>0 && motorDir(MOTOR_2)==ATRAS)
	MOVF	r0x07, W
	ADDLW	0x80
	ADDLW	0x80
	BNZ	_00262_DS_
	MOVLW	0x01
	SUBWF	r0x06, W
_00262_DS_:
	BNC	_00175_DS_
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_motorDir
	MOVWF	r0x08
	MOVF	POSTINC1, F
	MOVF	r0x08, W
	BNZ	_00175_DS_
	.line	181; motores.c	CCPR2L=0;
	CLRF	_CCPR2L
	BANKSEL	_stAveraged_nErrors_1_72
	.line	182; motores.c	nErrors=0;
	CLRF	_stAveraged_nErrors_1_72, B
	BANKSEL	(_stAveraged_nErrors_1_72 + 1)
	CLRF	(_stAveraged_nErrors_1_72 + 1), B
	.line	183; motores.c	current_state=&stWaitForMotor2Forward;
	MOVLW	LOW(_stWaitForMotor2Forward)
	BANKSEL	_current_state
	MOVWF	_current_state, B
	MOVLW	HIGH(_stWaitForMotor2Forward)
	BANKSEL	(_current_state + 1)
	MOVWF	(_current_state + 1), B
	MOVLW	UPPER(_stWaitForMotor2Forward)
	BANKSEL	(_current_state + 2)
	MOVWF	(_current_state + 2), B
	.line	184; motores.c	return;
	BRA	_00191_DS_
_00175_DS_:
	.line	187; motores.c	err1 = outSpeed1-width1;
	MOVF	r0x00, W
	SUBWF	r0x04, W
	MOVWF	r0x00
	MOVF	r0x01, W
	SUBWFB	r0x05, W
	MOVWF	r0x01
	BANKSEL	(_stAveraged_nErrors_1_72 + 1)
	.line	188; motores.c	errors1[nErrors]=err1;
	MOVF	(_stAveraged_nErrors_1_72 + 1), W, B
	MOVWF	POSTDEC1
	BANKSEL	_stAveraged_nErrors_1_72
	MOVF	_stAveraged_nErrors_1_72, W, B
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x02
	MOVWF	POSTDEC1
	CALL	__mulint
	MOVWF	r0x08
	MOVFF	PRODL, r0x09
	MOVLW	0x04
	ADDWF	FSR1L, F
	MOVLW	LOW(_stAveraged_errors1_1_72)
	ADDWF	r0x08, F
	MOVLW	HIGH(_stAveraged_errors1_1_72)
	ADDWFC	r0x09, F
	MOVFF	r0x08, FSR0L
	MOVFF	r0x09, FSR0H
	MOVFF	r0x00, POSTINC0
	MOVFF	r0x01, INDF0
	.line	190; motores.c	err2 = outSpeed2-width2;
	MOVF	r0x02, W
	SUBWF	r0x06, W
	MOVWF	r0x02
	MOVF	r0x03, W
	SUBWFB	r0x07, W
	MOVWF	r0x03
	BANKSEL	(_stAveraged_nErrors_1_72 + 1)
	.line	191; motores.c	errors2[nErrors]=err2;
	MOVF	(_stAveraged_nErrors_1_72 + 1), W, B
	MOVWF	POSTDEC1
	BANKSEL	_stAveraged_nErrors_1_72
	MOVF	_stAveraged_nErrors_1_72, W, B
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x02
	MOVWF	POSTDEC1
	CALL	__mulint
	MOVWF	r0x08
	MOVFF	PRODL, r0x09
	MOVLW	0x04
	ADDWF	FSR1L, F
	MOVLW	LOW(_stAveraged_errors2_1_72)
	ADDWF	r0x08, F
	MOVLW	HIGH(_stAveraged_errors2_1_72)
	ADDWFC	r0x09, F
	MOVFF	r0x08, FSR0L
	MOVFF	r0x09, FSR0H
	MOVFF	r0x02, POSTINC0
	MOVFF	r0x03, INDF0
	BANKSEL	_stAveraged_nErrors_1_72
	.line	193; motores.c	if (++nErrors == TOTAL_ERRORS)
	INCFSZ	_stAveraged_nErrors_1_72, F, B
	BRA	_10371_DS_
	BANKSEL	(_stAveraged_nErrors_1_72 + 1)
	INCF	(_stAveraged_nErrors_1_72 + 1), F, B
_10371_DS_:
	BANKSEL	_stAveraged_nErrors_1_72
	MOVF	_stAveraged_nErrors_1_72, W, B
	XORLW	0x03
	BNZ	_00263_DS_
	BANKSEL	(_stAveraged_nErrors_1_72 + 1)
	MOVF	(_stAveraged_nErrors_1_72 + 1), W, B
	BZ	_00264_DS_
_00263_DS_:
	BRA	_00188_DS_
_00264_DS_:
	BANKSEL	_stAveraged_nErrors_1_72
	.line	195; motores.c	nErrors=0;
	CLRF	_stAveraged_nErrors_1_72, B
	BANKSEL	(_stAveraged_nErrors_1_72 + 1)
	CLRF	(_stAveraged_nErrors_1_72 + 1), B
	.line	196; motores.c	for (n=0;n<TOTAL_ERRORS;n++)
	CLRF	r0x08
	CLRF	r0x09
	CLRF	r0x0a
	CLRF	r0x0b
_00189_DS_:
	.line	198; motores.c	err1+=errors1[n];
	MOVLW	LOW(_stAveraged_errors1_1_72)
	ADDWF	r0x0a, W
	MOVWF	r0x0c
	MOVLW	HIGH(_stAveraged_errors1_1_72)
	ADDWFC	r0x0b, W
	MOVWF	r0x0d
	MOVFF	r0x0c, FSR0L
	MOVFF	r0x0d, FSR0H
	MOVFF	POSTINC0, r0x0c
	MOVFF	INDF0, r0x0d
	MOVF	r0x0c, W
	ADDWF	r0x00, F
	MOVF	r0x0d, W
	ADDWFC	r0x01, F
	.line	199; motores.c	err2+=errors2[n];
	MOVLW	LOW(_stAveraged_errors2_1_72)
	ADDWF	r0x0a, W
	MOVWF	r0x0c
	MOVLW	HIGH(_stAveraged_errors2_1_72)
	ADDWFC	r0x0b, W
	MOVWF	r0x0d
	MOVFF	r0x0c, FSR0L
	MOVFF	r0x0d, FSR0H
	MOVFF	POSTINC0, r0x0c
	MOVFF	INDF0, r0x0d
	MOVF	r0x0c, W
	ADDWF	r0x02, F
	MOVF	r0x0d, W
	ADDWFC	r0x03, F
	.line	196; motores.c	for (n=0;n<TOTAL_ERRORS;n++)
	MOVLW	0x02
	ADDWF	r0x0a, F
	BTFSC	STATUS, 0
	INCF	r0x0b, F
	INFSNZ	r0x08, F
	INCF	r0x09, F
	MOVF	r0x09, W
	ADDLW	0x80
	ADDLW	0x80
	BNZ	_00265_DS_
	MOVLW	0x03
	SUBWF	r0x08, W
_00265_DS_:
	BNC	_00189_DS_
	.line	202; motores.c	err1/=TOTAL_ERRORS;
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x03
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	__divsint
	MOVWF	r0x00
	MOVFF	PRODL, r0x01
	MOVLW	0x04
	ADDWF	FSR1L, F
	.line	203; motores.c	err2/=TOTAL_ERRORS;
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x03
	MOVWF	POSTDEC1
	MOVF	r0x03, W
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	CALL	__divsint
	MOVWF	r0x02
	MOVFF	PRODL, r0x03
	MOVLW	0x04
	ADDWF	FSR1L, F
	.line	205; motores.c	if (err1<0 && err1<-LIMIT)	err1=-LIMIT;
	BSF	STATUS, 0
	BTFSS	r0x01, 7
	BCF	STATUS, 0
	BNC	_00178_DS_
	MOVF	r0x01, W
	ADDLW	0x80
	ADDLW	0x81
	BNZ	_00266_DS_
	MOVLW	0xf6
	SUBWF	r0x00, W
_00266_DS_:
	BC	_00178_DS_
	MOVLW	0xf6
	MOVWF	r0x00
	MOVLW	0xff
	MOVWF	r0x01
_00178_DS_:
	.line	206; motores.c	if (err2<0 && err2<-LIMIT)	err2=-LIMIT;
	BSF	STATUS, 0
	BTFSS	r0x03, 7
	BCF	STATUS, 0
	BNC	_00181_DS_
	MOVF	r0x03, W
	ADDLW	0x80
	ADDLW	0x81
	BNZ	_00267_DS_
	MOVLW	0xf6
	SUBWF	r0x02, W
_00267_DS_:
	BC	_00181_DS_
	MOVLW	0xf6
	MOVWF	r0x02
	MOVLW	0xff
	MOVWF	r0x03
_00181_DS_:
	.line	207; motores.c	if (err1 > LIMIT)	err1=LIMIT;
	MOVF	r0x01, W
	ADDLW	0x80
	ADDLW	0x80
	BNZ	_00268_DS_
	MOVLW	0x0b
	SUBWF	r0x00, W
_00268_DS_:
	BNC	_00184_DS_
	MOVLW	0x0a
	MOVWF	r0x00
	CLRF	r0x01
_00184_DS_:
	.line	208; motores.c	if (err2 > LIMIT)	err2=LIMIT;
	MOVF	r0x03, W
	ADDLW	0x80
	ADDLW	0x80
	BNZ	_00269_DS_
	MOVLW	0x0b
	SUBWF	r0x02, W
_00269_DS_:
	BNC	_00186_DS_
	MOVLW	0x0a
	MOVWF	r0x02
	CLRF	r0x03
_00186_DS_:
	.line	210; motores.c	CCPR1L = ( outSpeed1==0 ) ? 0 : CCPR1L+err1;
	MOVF	r0x04, W
	IORWF	r0x05, W
	BSF	STATUS, 0
	TSTFSZ	WREG
	BCF	STATUS, 0
	CLRF	r0x04
	RLCF	r0x04, F
	MOVF	r0x04, W
	BZ	_00193_DS_
	CLRF	r0x04
	BRA	_00194_DS_
_00193_DS_:
	MOVF	_CCPR1L, W
	MOVWF	r0x01
	MOVF	r0x00, W
	ADDWF	r0x01, W
	MOVWF	r0x04
_00194_DS_:
	MOVFF	r0x04, _CCPR1L
	.line	211; motores.c	CCPR2L = ( outSpeed2==0 ) ? 0 : CCPR2L+err2;
	MOVF	r0x06, W
	IORWF	r0x07, W
	BSF	STATUS, 0
	TSTFSZ	WREG
	BCF	STATUS, 0
	CLRF	r0x06
	RLCF	r0x06, F
	MOVF	r0x06, W
	BZ	_00195_DS_
	CLRF	r0x00
	BRA	_00196_DS_
_00195_DS_:
	MOVF	_CCPR2L, W
	MOVWF	r0x01
	MOVF	r0x02, W
	ADDWF	r0x01, W
	MOVWF	r0x00
_00196_DS_:
	MOVFF	r0x00, _CCPR2L
_00188_DS_:
	.line	213; motores.c	current_state=&stSampling;
	MOVLW	LOW(_stSampling)
	BANKSEL	_current_state
	MOVWF	_current_state, B
	MOVLW	HIGH(_stSampling)
	BANKSEL	(_current_state + 1)
	MOVWF	(_current_state + 1), B
	MOVLW	UPPER(_stSampling)
	BANKSEL	(_current_state + 2)
	MOVWF	(_current_state + 2), B
_00191_DS_:
	MOVFF	PREINC1, r0x0d
	MOVFF	PREINC1, r0x0c
	MOVFF	PREINC1, r0x0b
	MOVFF	PREINC1, r0x0a
	MOVFF	PREINC1, r0x09
	MOVFF	PREINC1, r0x08
	MOVFF	PREINC1, r0x07
	MOVFF	PREINC1, r0x06
	MOVFF	PREINC1, r0x05
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_motores__stWaitForMotor2Forward	code
_stWaitForMotor2Forward:
	.line	125; motores.c	void stWaitForMotor2Forward(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	BANKSEL	(_encoder + 17)
	.line	127; motores.c	if (encoder[MOTOR_2].inSpeed==0)
	MOVF	(_encoder + 17), W, B
	BANKSEL	(_encoder + 18)
	IORWF	(_encoder + 18), W, B
	BNZ	_00154_DS_
	.line	128; motores.c	motorChangeDir (ADELANTE,MOTOR_2);
	MOVLW	0x01
	MOVWF	POSTDEC1
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_motorChangeDir
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
_00154_DS_:
	.line	130; motores.c	current_state=&stSampling;
	MOVLW	LOW(_stSampling)
	BANKSEL	_current_state
	MOVWF	_current_state, B
	MOVLW	HIGH(_stSampling)
	BANKSEL	(_current_state + 1)
	MOVWF	(_current_state + 1), B
	MOVLW	UPPER(_stSampling)
	BANKSEL	(_current_state + 2)
	MOVWF	(_current_state + 2), B
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_motores__stWaitForMotor1Forward	code
_stWaitForMotor1Forward:
	.line	114; motores.c	void stWaitForMotor1Forward(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	BANKSEL	(_encoder + 4)
	.line	116; motores.c	if (encoder[MOTOR_1].inSpeed==0)
	MOVF	(_encoder + 4), W, B
	BANKSEL	(_encoder + 5)
	IORWF	(_encoder + 5), W, B
	BNZ	_00147_DS_
	.line	117; motores.c	motorChangeDir (ADELANTE,MOTOR_1);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_motorChangeDir
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
_00147_DS_:
	.line	119; motores.c	current_state=&stSampling;
	MOVLW	LOW(_stSampling)
	BANKSEL	_current_state
	MOVWF	_current_state, B
	MOVLW	HIGH(_stSampling)
	BANKSEL	(_current_state + 1)
	MOVWF	(_current_state + 1), B
	MOVLW	UPPER(_stSampling)
	BANKSEL	(_current_state + 2)
	MOVWF	(_current_state + 2), B
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_motores__stWaitForMotor2Bak	code
_stWaitForMotor2Bak:
	.line	103; motores.c	void stWaitForMotor2Bak(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	BANKSEL	(_encoder + 17)
	.line	105; motores.c	if (encoder[MOTOR_2].inSpeed==0)
	MOVF	(_encoder + 17), W, B
	BANKSEL	(_encoder + 18)
	IORWF	(_encoder + 18), W, B
	BNZ	_00140_DS_
	.line	106; motores.c	motorChangeDir (ATRAS,MOTOR_2);
	MOVLW	0x01
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_motorChangeDir
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
_00140_DS_:
	.line	108; motores.c	current_state=&stSampling;
	MOVLW	LOW(_stSampling)
	BANKSEL	_current_state
	MOVWF	_current_state, B
	MOVLW	HIGH(_stSampling)
	BANKSEL	(_current_state + 1)
	MOVWF	(_current_state + 1), B
	MOVLW	UPPER(_stSampling)
	BANKSEL	(_current_state + 2)
	MOVWF	(_current_state + 2), B
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_motores__stWaitForMotor1Bak	code
_stWaitForMotor1Bak:
	.line	92; motores.c	void stWaitForMotor1Bak(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	BANKSEL	(_encoder + 4)
	.line	94; motores.c	if (encoder[MOTOR_1].inSpeed==0)
	MOVF	(_encoder + 4), W, B
	BANKSEL	(_encoder + 5)
	IORWF	(_encoder + 5), W, B
	BNZ	_00133_DS_
	.line	95; motores.c	motorChangeDir (ATRAS,MOTOR_1);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_motorChangeDir
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
_00133_DS_:
	.line	97; motores.c	current_state=&stSampling;
	MOVLW	LOW(_stSampling)
	BANKSEL	_current_state
	MOVWF	_current_state, B
	MOVLW	HIGH(_stSampling)
	BANKSEL	(_current_state + 1)
	MOVWF	(_current_state + 1), B
	MOVLW	UPPER(_stSampling)
	BANKSEL	(_current_state + 2)
	MOVWF	(_current_state + 2), B
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_motores__stSampling	code
_stSampling:
	.line	35; motores.c	void stSampling(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	BANKSEL	_stSampling_enc_position_a_1_61
	.line	44; motores.c	enc_position_a <<=2;
	MOVF	_stSampling_enc_position_a_1_61, W, B
	BANKSEL	_stSampling_enc_position_a_1_61
	ADDWF	_stSampling_enc_position_a_1_61, F, B
	BANKSEL	(_stSampling_enc_position_a_1_61 + 1)
	RLCF	(_stSampling_enc_position_a_1_61 + 1), F, B
	BCF	STATUS, 0
	BANKSEL	_stSampling_enc_position_a_1_61
	RLCF	_stSampling_enc_position_a_1_61, F, B
	BANKSEL	(_stSampling_enc_position_a_1_61 + 1)
	RLCF	(_stSampling_enc_position_a_1_61 + 1), F, B
	.line	45; motores.c	enc_position_a |= ((PORTD & 0x0c)>>2);
	MOVLW	0x0c
	ANDWF	_PORTD, W
	MOVWF	r0x00
	RRNCF	r0x00, W
	RRNCF	WREG, W
	ANDLW	0x3f
	MOVWF	r0x00
	CLRF	r0x01
	MOVF	r0x00, W
	BANKSEL	_stSampling_enc_position_a_1_61
	IORWF	_stSampling_enc_position_a_1_61, F, B
	MOVF	r0x01, W
	BANKSEL	(_stSampling_enc_position_a_1_61 + 1)
	IORWF	(_stSampling_enc_position_a_1_61 + 1), F, B
	.line	46; motores.c	width1+=enc_states[ (enc_position_a & 0x0f)];
	MOVLW	0x0f
	BANKSEL	_stSampling_enc_position_a_1_61
	ANDWF	_stSampling_enc_position_a_1_61, W, B
	MOVWF	r0x00
	CLRF	r0x01
	MOVLW	LOW(_stSampling_enc_states_1_61)
	ADDWF	r0x00, F
	MOVLW	HIGH(_stSampling_enc_states_1_61)
	ADDWFC	r0x01, F
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, FSR0H
	MOVFF	INDF0, r0x00
	CLRF	r0x01
	BTFSC	r0x00, 7
	SETF	r0x01
	MOVF	r0x00, W
	BANKSEL	_stSampling_width1_1_61
	ADDWF	_stSampling_width1_1_61, F, B
	MOVF	r0x01, W
	BANKSEL	(_stSampling_width1_1_61 + 1)
	ADDWFC	(_stSampling_width1_1_61 + 1), F, B
	BANKSEL	_stSampling_enc_position_b_1_61
	.line	48; motores.c	enc_position_b <<=2;
	MOVF	_stSampling_enc_position_b_1_61, W, B
	BANKSEL	_stSampling_enc_position_b_1_61
	ADDWF	_stSampling_enc_position_b_1_61, F, B
	BANKSEL	(_stSampling_enc_position_b_1_61 + 1)
	RLCF	(_stSampling_enc_position_b_1_61 + 1), F, B
	BCF	STATUS, 0
	BANKSEL	_stSampling_enc_position_b_1_61
	RLCF	_stSampling_enc_position_b_1_61, F, B
	BANKSEL	(_stSampling_enc_position_b_1_61 + 1)
	RLCF	(_stSampling_enc_position_b_1_61 + 1), F, B
	.line	49; motores.c	enc_position_b |= (PORTD & 0x03);
	MOVLW	0x03
	ANDWF	_PORTD, W
	MOVWF	r0x00
	CLRF	r0x01
	MOVF	r0x00, W
	BANKSEL	_stSampling_enc_position_b_1_61
	IORWF	_stSampling_enc_position_b_1_61, F, B
	MOVF	r0x01, W
	BANKSEL	(_stSampling_enc_position_b_1_61 + 1)
	IORWF	(_stSampling_enc_position_b_1_61 + 1), F, B
	.line	50; motores.c	width2+=enc_states[ (enc_position_b & 0x0f)];
	MOVLW	0x0f
	BANKSEL	_stSampling_enc_position_b_1_61
	ANDWF	_stSampling_enc_position_b_1_61, W, B
	MOVWF	r0x00
	CLRF	r0x01
	MOVLW	LOW(_stSampling_enc_states_1_61)
	ADDWF	r0x00, F
	MOVLW	HIGH(_stSampling_enc_states_1_61)
	ADDWFC	r0x01, F
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, FSR0H
	MOVFF	INDF0, r0x00
	CLRF	r0x01
	BTFSC	r0x00, 7
	SETF	r0x01
	MOVF	r0x00, W
	BANKSEL	_stSampling_width2_1_61
	ADDWF	_stSampling_width2_1_61, F, B
	MOVF	r0x01, W
	BANKSEL	(_stSampling_width2_1_61 + 1)
	ADDWFC	(_stSampling_width2_1_61 + 1), F, B
	BANKSEL	_stSampling_tiempo_1_61
	.line	52; motores.c	if (++tiempo>=120) // 120 milisegundos = 480
	INCFSZ	_stSampling_tiempo_1_61, F, B
	BRA	_20372_DS_
	BANKSEL	(_stSampling_tiempo_1_61 + 1)
	INCF	(_stSampling_tiempo_1_61 + 1), F, B
_20372_DS_:
	BANKSEL	(_stSampling_tiempo_1_61 + 1)
	MOVF	(_stSampling_tiempo_1_61 + 1), W, B
	ADDLW	0x80
	ADDLW	0x80
	BNZ	_00127_DS_
	MOVLW	0x78
	BANKSEL	_stSampling_tiempo_1_61
	SUBWF	_stSampling_tiempo_1_61, W, B
_00127_DS_:
	BTFSS	STATUS, 0
	BRA	_00114_DS_
	BANKSEL	(_stSampling_width1_1_61 + 1)
	.line	78; motores.c	encoder[MOTOR_1].inSpeed=abs(width1);
	MOVF	(_stSampling_width1_1_61 + 1), W, B
	MOVWF	POSTDEC1
	BANKSEL	_stSampling_width1_1_61
	MOVF	_stSampling_width1_1_61, W, B
	MOVWF	POSTDEC1
	CALL	_abs
	MOVWF	r0x00
	MOVFF	PRODL, r0x01
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	MOVF	r0x00, W
	BANKSEL	(_encoder + 4)
	MOVWF	(_encoder + 4), B
	MOVF	r0x01, W
	BANKSEL	(_encoder + 5)
	MOVWF	(_encoder + 5), B
	BANKSEL	(_stSampling_width2_1_61 + 1)
	.line	79; motores.c	encoder[MOTOR_2].inSpeed=abs(width2);
	MOVF	(_stSampling_width2_1_61 + 1), W, B
	MOVWF	POSTDEC1
	BANKSEL	_stSampling_width2_1_61
	MOVF	_stSampling_width2_1_61, W, B
	MOVWF	POSTDEC1
	CALL	_abs
	MOVWF	r0x00
	MOVFF	PRODL, r0x01
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	MOVF	r0x00, W
	BANKSEL	(_encoder + 17)
	MOVWF	(_encoder + 17), B
	MOVF	r0x01, W
	BANKSEL	(_encoder + 18)
	MOVWF	(_encoder + 18), B
	BANKSEL	_stSampling_tiempo_1_61
	.line	80; motores.c	tiempo=0;
	CLRF	_stSampling_tiempo_1_61, B
	BANKSEL	(_stSampling_tiempo_1_61 + 1)
	CLRF	(_stSampling_tiempo_1_61 + 1), B
	BANKSEL	_stSampling_width1_1_61
	.line	81; motores.c	width1=0;
	CLRF	_stSampling_width1_1_61, B
	BANKSEL	(_stSampling_width1_1_61 + 1)
	CLRF	(_stSampling_width1_1_61 + 1), B
	BANKSEL	_stSampling_width2_1_61
	.line	82; motores.c	width2=0;
	CLRF	_stSampling_width2_1_61, B
	BANKSEL	(_stSampling_width2_1_61 + 1)
	CLRF	(_stSampling_width2_1_61 + 1), B
	.line	84; motores.c	current_state=&stAveraged;
	MOVLW	LOW(_stAveraged)
	BANKSEL	_current_state
	MOVWF	_current_state, B
	MOVLW	HIGH(_stAveraged)
	BANKSEL	(_current_state + 1)
	MOVWF	(_current_state + 1), B
	MOVLW	UPPER(_stAveraged)
	BANKSEL	(_current_state + 2)
	MOVWF	(_current_state + 2), B
	BRA	_00116_DS_
_00114_DS_:
	.line	87; motores.c	current_state=&stSampling;
	MOVLW	LOW(_stSampling)
	BANKSEL	_current_state
	MOVWF	_current_state, B
	MOVLW	HIGH(_stSampling)
	BANKSEL	(_current_state + 1)
	MOVWF	(_current_state + 1), B
	MOVLW	UPPER(_stSampling)
	BANKSEL	(_current_state + 2)
	MOVWF	(_current_state + 2), B
_00116_DS_:
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_motores__abs	code
_abs:
	.line	28; motores.c	int abs(int j)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	.line	30; motores.c	return (j >= 0) ? j : -j;
	BSF	STATUS, 0
	BTFSS	r0x01, 7
	BCF	STATUS, 0
	CLRF	r0x02
	RLCF	r0x02, F
	MOVF	r0x02, W
	BSF	STATUS, 0
	TSTFSZ	WREG
	BCF	STATUS, 0
	CLRF	r0x02
	RLCF	r0x02, F
	MOVF	r0x02, W
	BZ	_00107_DS_
	MOVFF	r0x00, r0x02
	MOVFF	r0x01, r0x03
	BRA	_00108_DS_
_00107_DS_:
	COMF	r0x01, W
	MOVWF	r0x03
	COMF	r0x00, W
	MOVWF	r0x02
	INFSNZ	r0x02, F
	INCF	r0x03, F
_00108_DS_:
	MOVFF	r0x03, PRODL
	MOVF	r0x02, W
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
___str_0:
	DB	0x49, 0x6e, 0x69, 0x74, 0x69, 0x61, 0x6c, 0x69, 0x7a, 0x65, 0x20, 0x4d
	DB	0x6f, 0x74, 0x6f, 0x72, 0x73, 0x20, 0x25, 0x78, 0x0a, 0x0d, 0x00
; ; Starting pCode block
___str_1:
	DB	0x6d, 0x6f, 0x74, 0x6f, 0x72, 0x49, 0x6e, 0x76, 0x65, 0x72, 0x74, 0x44
	DB	0x69, 0x72, 0x0a, 0x0d, 0x00
; ; Starting pCode block
___str_2:
	DB	0x6d, 0x6f, 0x74, 0x6f, 0x72, 0x43, 0x68, 0x61, 0x6e, 0x67, 0x65, 0x44
	DB	0x69, 0x72, 0x0a, 0x0d, 0x00


; Statistics:
; code size:	 2794 (0x0aea) bytes ( 2.13%)
;           	 1397 (0x0575) words
; udata size:	   42 (0x002a) bytes ( 2.34%)
; access size:	   14 (0x000e) bytes


	end
