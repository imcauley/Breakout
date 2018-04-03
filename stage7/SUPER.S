	_xref	_supe_mode
; supervisor mode section of the program

_supe_mode
	move.l	old_ssp(pc),-(sp)	; return to user mode, restoring
	move.w	#$20,-(sp)		;   system stack pointer
	trap	#1
	addq.l	#6,sp

	move.w	#0,-(sp)	; return to caller
	move.w	#$4C,-(sp)
	trap	#1


	end	start
