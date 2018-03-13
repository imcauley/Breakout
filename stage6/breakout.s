; Generated by c68 v4.4.5, 25 Jan 95 (Jan 25 1995) from "./input.c"
	text
	even
_get_input:
	link	a6,#0
	;line	11
	move.w	#8,-(a7)
	jsr	__trap_1_w
L1:
	unlk	a6
	rts
_key_pressed:
	link	a6,#-4
	;line	17
	move.w	#11,-(a7)
	jsr	__trap_1_w
	addq.l	#2,a7
	ext.l	d0
	move.l	d0,-4(a6)
	;line	17
	tst.l	-4(a6)
	bne	L2
	;line	19
	moveq	#0,d0
	bra	L3
	bra	L4
L2:
	;line	22
	moveq	#1,d0
L4:
L3:
	unlk	a6
	rts
_get_time:
	link	a6,#-12
	;line	15
	pea	0
	move.w	#32,-(a7)
	jsr	__trap_1_wl
	addq.l	#6,a7
	move.l	d0,-12(a6)
	;line	16
	move.l	#1122,-4(a6)
	;line	17
	move.l	-4(a6),a0
	move.l	(a0),-8(a6)
	;line	18
	move.l	-12(a6),-(a7)
	move.w	#32,-(a7)
	jsr	__trap_1_wl
	;line	19
	move.l	-8(a6),d0
L5:
	unlk	a6
	rts
_get_base:
	link	a6,#-6
	movem.l	d3/d4,-(a7)
	;line	26
	move.l	8(a6),d4
	;line	27
	move.w	d4,d3
	;line	28
	clr.l	d0
	move.w	d3,d0
	divu	#256,d0
	swap	d0
	move.w	d0,d3
	;line	29
	move.w	#256,d0
	sub.w	d3,d0
	move.w	d0,d3
	;line	30
	move.l	d4,d0
	clr.l	d1
	move.w	d3,d1
	add.l	d1,d0
L6:
	movem.l	(a7)+,d3/d4
	unlk	a6
	rts
_main:
	link	a6,#-1106
	movem.l	d3/d4/d5/d6/d7/a3/a4/a5,-(a7)
	lea	__trap_14_w,a3
	;line	50
	move.w	#2,-(a7)
	jsr	(a3)
	addq.l	#2,a7
	move.l	d0,d4
	move.w	#2,-(a7)
	jsr	(a3)
	addq.l	#2,a7
	move.l	d0,-8(a6)
	pea	_buffer2
	jsr	_get_base
	addq.l	#4,a7
	move.l	d0,d3
	move.l	d3,a5
	move.l	d3,a4
	move.l	a5,d7
	moveq	#0,d6
	jsr	_get_time
	move.l	d0,-40(a6)
	moveq	#0,d5
	;line	50
	pea	-1106(a6)
	jsr	_start_game
	addq.l	#4,a7
	;line	51
	pea	-1106(a6)
	move.l	-8(a6),-(a7)
	move.l	d4,-(a7)
	jsr	_simple_render
	lea	12(a7),a7
	;line	53
	bra	L8
L7:
	;line	56
	jsr	_key_pressed
	cmp.w	#1,d0
	bne	L10
	;line	58
	jsr	_get_input
	move.l	d0,d6
	;line	59
	move.l	d6,-(a7)
	pea	-106(a6)
	pea	-86(a6)
	jsr	_asynch_events
	lea	12(a7),a7
	;line	60
	pea	-1106(a6)
	move.l	d7,-(a7)
	move.l	a4,-(a7)
	jsr	_simple_render
	lea	12(a7),a7
	;line	61
	move.w	#37,-(a7)
	jsr	(a3)
	addq.l	#2,a7
	;line	62
	cmp.w	#1,d5
	bne	L11
	;line	64
	move.l	d3,a4
	;line	65
	move.l	a5,d7
	;line	66
	move.w	#-1,-(a7)
	move.l	d4,-(a7)
	pea	-1
	move.w	#5,-(a7)
	jsr	__trap_14_wllw
	lea	12(a7),a7
	;line	67
	moveq	#0,d5
	bra	L12
L11:
	;line	71
	move.l	d4,a4
	;line	72
	move.l	-8(a6),d7
	;line	73
	move.w	#-1,-(a7)
	move.l	d3,-(a7)
	pea	-1
	move.w	#5,-(a7)
	jsr	__trap_14_wllw
	lea	12(a7),a7
	;line	74
	moveq	#1,d5
L12:
L10:
L8:
	cmp.l	#1048689,d6
	bne	L7
L9:
	;line	105
	move.w	#-1,-(a7)
	move.l	d4,-(a7)
	pea	-1
	move.w	#5,-(a7)
	jsr	__trap_14_wllw
	lea	12(a7),a7
	;line	106
	move.w	#37,-(a7)
	jsr	(a3)
	;line	108
	moveq	#0,d0
L13:
	movem.l	-1138(a6),d3/d4/d5/d6/d7/a3/a4/a5
	unlk	a6
	rts
	globl	_get_input
	globl	_key_pressed
	bss
_buffer2:
	ds.b	32500
	globl	_buffer2
	globl	_get_time
	globl	_get_base
	globl	_main
