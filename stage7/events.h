/*=========================================

Source File:
events.h

Author(s):
Daniel Jackins
Isaac McAuley

Date Last Changed:
April 7 2018

Class: COMP 2659 - 001
Instructor: Paul Pospisil

==========================================*/


void asynch_events(Paddle *paddle, Ball *ball, UINT8 input);
void synch_events(Paddle *paddle, Ball *ball, Brick bricks[][]);
void condition_events(Paddle *paddle, Ball *ball, Brick bricks[][], Score *score, Lives *lives);
void die(Ball *ball, Lives *lives);
