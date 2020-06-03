;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.0 #8981 (Apr  5 2014) (Linux)
; This file was generated Mon Sep  1 01:28:50 2014
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------

	.ident "SDCC version 3.4.0 #8981 [pic16 port]"
	.file	"delay.c"
	list	p=18f4455
	radix	dec


;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	_ContadorA
	global	_ContadorB
	global	_ContadorC
	global	_delay_1ms
	global	_delay_ms

;--------------------------------------------------------
;	Equates to used internal registers
;--------------------------------------------------------
STATUS	equ	0xfd8
FSR1L	equ	0xfe1
FSR2L	equ	0xfd9
POSTDEC1	equ	0xfe5
PREINC1	equ	0xfe4
PLUSW2	equ	0xfdb


; Internal registers
.registers	udata_ovr	0x0000
r0x00	res	1
r0x01	res	1
r0x02	res	1
r0x03	res	1

udata_delay_0	udata
_ContadorC	res	1

udata_delay_1	udata
_ContadorB	res	1

udata_delay_2	udata
_ContadorA	res	1

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; I code from now on!
; ; Starting pCode block
S_delay__delay_ms	code
_delay_ms:
	.line	29; delay.c	void delay_ms (unsigned long ms)
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
	MOVLW	0x05
	MOVFF	PLUSW2, r0x03
_00112_DS_:
	.line	31; delay.c	for (;ms>0;ms--)
	MOVF	r0x00, W
	IORWF	r0x01, W
	IORWF	r0x02, W
	IORWF	r0x03, W
	BZ	_00114_DS_
	.line	32; delay.c	delay_1ms();
	CALL	_delay_1ms
	.line	31; delay.c	for (;ms>0;ms--)
	MOVLW	0xff
	ADDWF	r0x00, F
	ADDWFC	r0x01, F
	ADDWFC	r0x02, F
	ADDWFC	r0x03, F
	BRA	_00112_DS_
_00114_DS_:
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_delay__delay_1ms	code
_delay_1ms:
	.line	4; delay.c	void delay_1ms (void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	; Código de retardo generado por PikLoops (sáb nov-2009-14 02:57:28)
	; Tiempo de retardo = 0.00099980 con Osc = 20.00000000MHz
retraso_0.001_seg:
	movlw D'7'
	movwf _ContadorB
	movlw D'124'
	movwf _ContadorA
retraso_0.001_seg_bucle:
	decfsz _ContadorA,1
	goto retraso_0.001_seg_bucle
	decfsz _ContadorB,1
	goto retraso_0.001_seg_bucle
	MOVFF	PREINC1, FSR2L
	RETURN	



; Statistics:
; code size:	  134 (0x0086) bytes ( 0.10%)
;           	   67 (0x0043) words
; udata size:	    3 (0x0003) bytes ( 0.17%)
; access size:	    4 (0x0004) bytes


	end
