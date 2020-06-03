;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.0 #8981 (Apr  5 2014) (Linux)
; This file was generated Mon Sep  1 01:28:51 2014
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------

	.ident "SDCC version 3.4.0 #8981 [pic16 port]"
	.file	"i2c_master.c"
	list	p=18f4455
	radix	dec


;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	_i2c_open
	global	_i2c_start
	global	_i2c_stop
	global	_i2c_restart
	global	_i2c_ack
	global	_i2c_nack
	global	_i2c_wait
	global	_i2c_readchar
	global	_i2c_readstr
	global	_i2c_writechar
	global	_i2c_writestr

;--------------------------------------------------------
; extern variables in this module
;--------------------------------------------------------
	extern	__gptrput1
	extern	__gptrget1
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

;--------------------------------------------------------
;	Equates to used internal registers
;--------------------------------------------------------
STATUS	equ	0xfd8
WREG	equ	0xfe8
FSR0L	equ	0xfe9
FSR1L	equ	0xfe1
FSR2L	equ	0xfd9
POSTINC1	equ	0xfe6
POSTDEC1	equ	0xfe5
PREINC1	equ	0xfe4
PLUSW2	equ	0xfdb
PRODL	equ	0xff3


; Internal registers
.registers	udata_ovr	0x0000
r0x00	res	1
r0x01	res	1
r0x02	res	1
r0x03	res	1
r0x04	res	1
r0x05	res	1

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; I code from now on!
; ; Starting pCode block
S_i2c_master__i2c_writestr	code
_i2c_writestr:
	.line	117; i2c_master.c	char i2c_writestr(unsigned char *ptr, unsigned char len) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
	MOVLW	0x05
	MOVFF	PLUSW2, r0x03
_00175_DS_:
	.line	118; i2c_master.c	while( len-- ) {                      // now send out the string
	MOVFF	r0x03, r0x04
	DECF	r0x03, F
	MOVF	r0x04, W
	BZ	_00177_DS_
	.line	122; i2c_master.c	i2c_writechar(*ptr);
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, PRODL
	MOVF	r0x02, W
	CALL	__gptrget1
	MOVWF	r0x04
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	CALL	_i2c_writechar
	MOVF	POSTINC1, F
	.line	126; i2c_master.c	ptr++;
	INCF	r0x00, F
	BNC	_00175_DS_
	INFSNZ	r0x01, F
	INCF	r0x02, F
_00187_DS_:
	BRA	_00175_DS_
_00177_DS_:
	.line	128; i2c_master.c	return 0;
	CLRF	WREG
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_i2c_master__i2c_writechar	code
_i2c_writechar:
	.line	110; i2c_master.c	char i2c_writechar(unsigned char dat) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVLW	0x02
	MOVFF	PLUSW2, _SSPBUF
	.line	112; i2c_master.c	i2c_wait();
	CALL	_i2c_wait
	.line	113; i2c_master.c	return 0;
	CLRF	WREG
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_i2c_master__i2c_readstr	code
_i2c_readstr:
	.line	87; i2c_master.c	char i2c_readstr(unsigned char *ptr, unsigned char len) {
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
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
	MOVLW	0x05
	MOVFF	PLUSW2, r0x03
	.line	89; i2c_master.c	while( len-- ) {
	CLRF	r0x04
_00150_DS_:
	MOVFF	r0x03, r0x05
	DECF	r0x03, F
	MOVF	r0x05, W
	BZ	_00152_DS_
	.line	93; i2c_master.c	*ptr = i2c_readchar();
	CALL	_i2c_readchar
	MOVWF	r0x05
	MOVFF	r0x05, POSTDEC1
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, PRODL
	MOVF	r0x02, W
	CALL	__gptrput1
	.line	97; i2c_master.c	if (len) i2c_ack();
	MOVF	r0x03, W
	BZ	_00149_DS_
	CALL	_i2c_ack
_00149_DS_:
	.line	98; i2c_master.c	ptr++;
	INCF	r0x00, F
	BNC	_00165_DS_
	INFSNZ	r0x01, F
	INCF	r0x02, F
_00165_DS_:
	.line	99; i2c_master.c	count++;
	INCF	r0x04, F
	BRA	_00150_DS_
_00152_DS_:
	.line	101; i2c_master.c	return count;
	MOVF	r0x04, W
	MOVFF	PREINC1, r0x05
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_i2c_master__i2c_readchar	code
_i2c_readchar:
	.line	78; i2c_master.c	unsigned char i2c_readchar(void) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	79; i2c_master.c	SSPCON2bits.RCEN = 1;		// Enable receive
	BSF	_SSPCON2bits, 3
	.line	80; i2c_master.c	i2c_wait();
	CALL	_i2c_wait
	.line	81; i2c_master.c	return SSPBUF;
	MOVF	_SSPBUF, W
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_i2c_master__i2c_wait	code
_i2c_wait:
	.line	72; i2c_master.c	void i2c_wait(void) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
_00135_DS_:
	.line	73; i2c_master.c	while (!PIR1bits.SSPIF) ;
	BTFSS	_PIR1bits, 3
	BRA	_00135_DS_
	.line	74; i2c_master.c	PIR1bits.SSPIF = 0;
	BCF	_PIR1bits, 3
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_i2c_master__i2c_nack	code
_i2c_nack:
	.line	65; i2c_master.c	void i2c_nack(void) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	66; i2c_master.c	SSPCON2bits.ACKDT = 1;
	BSF	_SSPCON2bits, 5
	.line	67; i2c_master.c	SSPCON2bits.ACKEN = 1;
	BSF	_SSPCON2bits, 4
	.line	68; i2c_master.c	i2c_wait();
	CALL	_i2c_wait
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_i2c_master__i2c_ack	code
_i2c_ack:
	.line	59; i2c_master.c	void i2c_ack(void) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	60; i2c_master.c	SSPCON2bits.ACKDT = 0;
	BCF	_SSPCON2bits, 5
	.line	61; i2c_master.c	SSPCON2bits.ACKEN = 1;
	BSF	_SSPCON2bits, 4
	.line	62; i2c_master.c	i2c_wait();
	CALL	_i2c_wait
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_i2c_master__i2c_restart	code
_i2c_restart:
	.line	53; i2c_master.c	void i2c_restart(void) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	54; i2c_master.c	SSPCON2bits.RSEN = 1;
	BSF	_SSPCON2bits, 1
	.line	55; i2c_master.c	i2c_wait();
	CALL	_i2c_wait
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_i2c_master__i2c_stop	code
_i2c_stop:
	.line	46; i2c_master.c	void i2c_stop(void) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	47; i2c_master.c	PIR1bits.SSPIF = 0;
	BCF	_PIR1bits, 3
	.line	48; i2c_master.c	SSPCON2bits.PEN = 1;
	BSF	_SSPCON2bits, 2
	.line	49; i2c_master.c	i2c_wait();
	CALL	_i2c_wait
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_i2c_master__i2c_start	code
_i2c_start:
	.line	39; i2c_master.c	void i2c_start(void) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	40; i2c_master.c	PIR1bits.SSPIF = 0;
	BCF	_PIR1bits, 3
	.line	41; i2c_master.c	SSPCON2bits.SEN = 1;
	BSF	_SSPCON2bits, 0
	.line	42; i2c_master.c	i2c_wait();
	CALL	_i2c_wait
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_i2c_master__i2c_open	code
_i2c_open:
	.line	13; i2c_master.c	void i2c_open(unsigned char mode, unsigned char slew, unsigned char addr_brd) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
	.line	14; i2c_master.c	SSPSTAT &= 0x3f;
	MOVLW	0x3f
	ANDWF	_SSPSTAT, F
	.line	15; i2c_master.c	SSPCON1 = 0;
	CLRF	_SSPCON1
	.line	16; i2c_master.c	SSPCON2 = 0;
	CLRF	_SSPCON2
	.line	17; i2c_master.c	SSPCON1 |= mode;
	MOVF	r0x00, W
	IORWF	_SSPCON1, F
	.line	18; i2c_master.c	SSPSTAT |= slew;
	MOVF	r0x01, W
	IORWF	_SSPSTAT, F
	.line	22; i2c_master.c	TRISBbits.TRISB1 = 1;
	BSF	_TRISBbits, 1
	.line	23; i2c_master.c	TRISBbits.TRISB0 = 1;
	BSF	_TRISBbits, 0
	.line	33; i2c_master.c	SSPADD = addr_brd;
	MOVFF	r0x02, _SSPADD
	.line	35; i2c_master.c	SSPCON1 |= 0x20;
	BSF	_SSPCON1, 5
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	



; Statistics:
; code size:	  528 (0x0210) bytes ( 0.40%)
;           	  264 (0x0108) words
; udata size:	    0 (0x0000) bytes ( 0.00%)
; access size:	    6 (0x0006) bytes


	end
