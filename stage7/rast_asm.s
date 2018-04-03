  xdef  _set_screen_base

SCREEN_ADS  equ FFFF8201
NEW_SCREEN  equ 8

_set_screen_base:
  link  a6,#0
  movem d0-d5,-(sp)

  movep NEW_SCREEN(sp),#$SCREEN_ADS

  movem -(sp),d0-d5
  unlk  a6
  rts
