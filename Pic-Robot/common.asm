;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.0 #8981 (Apr  5 2014) (Linux)
; This file was generated Mon Sep  1 01:28:50 2014
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------

	.ident "SDCC version 3.4.0 #8981 [pic16 port]"
	.file	"common.c"
	list	p=18f4455
	radix	dec


;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	_labs
	global	_atoi

;--------------------------------------------------------
; extern variables in this module
;--------------------------------------------------------
	extern	__gptrget1
	extern	__mulint

;--------------------------------------------------------
;	Equates to used internal registers
;--------------------------------------------------------
STATUS	equ	0xfd8
WREG	equ	0xfe8
FSR0L	equ	0xfe9
FSR1L	equ	0xfe1
FSR2L	equ	0xfd9
POSTDEC1	equ	0xfe5
PREINC1	equ	0xfe4
PLUSW2	equ	0xfdb
PRODL	equ	0xff3
PRODH	equ	0xff4


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

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; I code from now on!
; ; Starting pCode block
S_common__atoi	code
_atoi:
	.line	6; common.c	int atoi(char * s)
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
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
	.line	8; common.c	int rv=0; 
	CLRF	r0x03
	CLRF	r0x04
	.line	9; common.c	char sign = 0;
	CLRF	r0x05
	.line	12; common.c	while (*s) 
	MOVFF	r0x00, r0x06
	MOVFF	r0x01, r0x07
	MOVFF	r0x02, r0x08
_00123_DS_:
	MOVFF	r0x06, FSR0L
	MOVFF	r0x07, PRODL
	MOVF	r0x08, W
	CALL	__gptrget1
	MOVWF	r0x09
	MOVF	r0x09, W
	BZ	_00152_DS_
	.line	14; common.c	if (*s <= '9' && *s >= '0')
	MOVF	r0x09, W
	ADDLW	0x80
	ADDLW	0x46
	BC	_00118_DS_
	MOVF	r0x09, W
	ADDLW	0x80
	ADDLW	0x50
	BC	_00152_DS_
_00118_DS_:
	.line	16; common.c	if (*s == '-' || *s == '+') 
	MOVFF	r0x06, FSR0L
	MOVFF	r0x07, PRODL
	MOVF	r0x08, W
	CALL	__gptrget1
	MOVWF	r0x09
	MOVF	r0x09, W
	XORLW	0x2d
	BZ	_00152_DS_
	MOVF	r0x09, W
	XORLW	0x2b
	BZ	_00152_DS_
	.line	18; common.c	s++;
	INCF	r0x06, F
	BNC	_00184_DS_
	INFSNZ	r0x07, F
	INCF	r0x08, F
_00184_DS_:
	BRA	_00123_DS_
_00152_DS_:
	MOVFF	r0x06, r0x00
	MOVFF	r0x07, r0x01
	MOVFF	r0x08, r0x02
	.line	21; common.c	if(*s == '-')sign=1;
	MOVFF	r0x06, FSR0L
	MOVFF	r0x07, PRODL
	MOVF	r0x08, W
	CALL	__gptrget1
	MOVWF	r0x06
	CLRF	r0x07
	MOVF	r0x06, W
	XORLW	0x2d
	BNZ	_00186_DS_
	INCF	r0x07, F
_00186_DS_:
	MOVF	r0x07, W
	BZ	_00127_DS_
	MOVLW	0x01
	MOVWF	r0x05
_00127_DS_:
	.line	23; common.c	if (*s == '-' || *s == '+') s++;
	MOVF	r0x07, W
	BNZ	_00128_DS_
	MOVF	r0x06, W
	XORLW	0x2b
	BNZ	_00150_DS_
_00128_DS_:
	INCF	r0x00, F
	BNC	_00150_DS_
	INFSNZ	r0x01, F
	INCF	r0x02, F
_00189_DS_:
_00150_DS_:
_00133_DS_:
	.line	25; common.c	while (*s && *s >= '0' && *s <= '9') 
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, PRODL
	MOVF	r0x02, W
	CALL	__gptrget1
	MOVWF	r0x06
	MOVF	r0x06, W
	BZ	_00135_DS_
	MOVF	r0x06, W
	ADDLW	0x80
	ADDLW	0x50
	BNC	_00135_DS_
	MOVF	r0x06, W
	ADDLW	0x80
	ADDLW	0x46
	BC	_00135_DS_
	.line	27; common.c	rv = (rv * 10) + (*s - '0');
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	MOVF	r0x03, W
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x0a
	MOVWF	POSTDEC1
	CALL	__mulint
	MOVWF	r0x07
	MOVFF	PRODL, r0x08
	MOVLW	0x04
	ADDWF	FSR1L, F
	CLRF	r0x09
	BTFSC	r0x06, 7
	SETF	r0x09
	MOVLW	0xd0
	ADDWF	r0x06, F
	BTFSS	STATUS, 0
	DECF	r0x09, F
	MOVF	r0x06, W
	ADDWF	r0x07, W
	MOVWF	r0x03
	MOVF	r0x09, W
	ADDWFC	r0x08, W
	MOVWF	r0x04
	.line	28; common.c	s++;
	INCF	r0x00, F
	BNC	_00192_DS_
	INFSNZ	r0x01, F
	INCF	r0x02, F
_00192_DS_:
	BRA	_00133_DS_
_00135_DS_:
	.line	31; common.c	return (sign ? -rv : rv);
	MOVF	r0x05, W
	BZ	_00138_DS_
	COMF	r0x04, W
	MOVWF	r0x01
	COMF	r0x03, W
	MOVWF	r0x00
	INFSNZ	r0x00, F
	INCF	r0x01, F
	BRA	_00139_DS_
_00138_DS_:
	MOVFF	r0x03, r0x00
	MOVFF	r0x04, r0x01
_00139_DS_:
	MOVFF	r0x01, PRODL
	MOVF	r0x00, W
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
S_common__labs	code
_labs:
	.line	1; common.c	long labs (long i) 
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
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
	MOVLW	0x05
	MOVFF	PLUSW2, r0x03
	.line	3; common.c	return i < 0 ? -i : i;
	BSF	STATUS, 0
	BTFSS	r0x03, 7
	BCF	STATUS, 0
	BNC	_00107_DS_
	COMF	r0x03, W
	MOVWF	r0x07
	COMF	r0x02, W
	MOVWF	r0x06
	COMF	r0x01, W
	MOVWF	r0x05
	COMF	r0x00, W
	MOVWF	r0x04
	INCF	r0x04, F
	BNZ	_00108_DS_
	INCF	r0x05, F
	BNZ	_00108_DS_
	INFSNZ	r0x06, F
	INCF	r0x07, F
_00112_DS_:
	BRA	_00108_DS_
_00107_DS_:
	MOVFF	r0x00, r0x04
	MOVFF	r0x01, r0x05
	MOVFF	r0x02, r0x06
	MOVFF	r0x03, r0x07
_00108_DS_:
	MOVFF	r0x07, FSR0L
	MOVFF	r0x06, PRODH
	MOVFF	r0x05, PRODL
	MOVF	r0x04, W
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



; Statistics:
; code size:	  572 (0x023c) bytes ( 0.44%)
;           	  286 (0x011e) words
; udata size:	    0 (0x0000) bytes ( 0.00%)
; access size:	   10 (0x000a) bytes


	end
