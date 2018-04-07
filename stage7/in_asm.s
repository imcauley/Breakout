	xdef	_key_isr
	xref	_key_press

SERVICE_B	equ	$ffA11
_key_isr:	
	movem.l	d0-d6/a0-a6,-(sp)
	jsr _key_press
	move.b	($fffffa11),d0
	and.b	#$BF,d0
	move.b	d0,($fffffa11)
	movem.l	(sp)+,d0-d6/a0-a6
	rte