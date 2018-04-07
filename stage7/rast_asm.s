	xdef  _set_screen_base
  
SCREEN_ADS  equ $ffff8201
NEW_SCREEN  equ 12

_set_screen_base:
	link  a6,#0
	movem d0/a0,-(sp)
 
  
	clr.l	d0
	move.l	NEW_SCREEN(sp),d0
	lsr.l	#8,d0
	lea	SCREEN_ADS,a0
	movep d0,0(a0)
  

	movem (sp)+,d0/a0
	unlk  a6
	rts
  