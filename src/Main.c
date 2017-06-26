#include "nios2_ctrl_reg_macros.h"
#if !PRINT
	#include <stdio.h>
	#define PRINT
#endif
#if !PROTOTYPE
	#include "prototypes.h"
#endif
/* key_pressed and pattern are written by interrupt service routines; we have to declare
* these as volatile to avoid the compiler caching their values in registers */

//volatile int direction = 1;
volatile int currentDirection = 1;
volatile int yPos = 120;
volatile int start = 0, playAgain = 0;
const short wallColor = (short) 0b1111100000000000;
extern struct Snake *head;
volatile int welcome = 1;
int counter = 8000000; // 1/(100 MHz) × (5000000) = 50 msec
extern int score;


/**
 * Function that displays initial score of the game
 */
void setInfoBar()
{
	char snakeText[10] = "Snake\0";
	char scoreText[10] = "Score\0";
	VGA_text(37,2,snakeText);
	VGA_text(61, 2,scoreText);
}

/**
 * Function that displays beginning of game text
 */
void welcomeScreen()
{
	char welcomeText[] = "Welcome to Snake!\0";
	char howToStart[] = "Press any button to start.\0";
	VGA_text(33,24,welcomeText);
	VGA_text(29, 32,howToStart);
	welcome = 1;
}

/**
 * Initialize entire game including drawing starting positions, text, and score
 */
void initialization()
{
	score = 0;
	counter = 8000000;
    volatile int * interval_timer_ptr = (int *) 0xFF202000; // interval timer base address

    /* set the interval timer period for iterating game */
    *(interval_timer_ptr + 0x2) = (counter & 0xFFFF);
    *(interval_timer_ptr + 0x3) = (counter >> 16) & 0xFFFF;
    /* start interval timer, enable its interrupts */
    *(interval_timer_ptr + 1) = 0x7; // STOP = 0, START = 1, CONT = 1, ITO = 1

	clearscreen();
	clearText();
	welcomeScreen();
	setInfoBar();
	buildWall(wallColor);
	setScore();
    initSnake();
		for (int i =0; i <3; i++){
			insertLink(head);
		}
	generateFood(head);
	printf("Game Initialization complete \n");
}




int main(void){
  /* Declare volatile pointers to I/O registers (volatile means that IO load and store instructions
  * will be used to access these pointer locations instead of regular memory loads and stores) */
  volatile int * interval_timer_ptr = (int *) 0xFF202000; // interval timer base address
  volatile int * KEY_ptr = (int *) 0xFF200050; // pushbutton KEY address
  /* set the interval timer period for iterating game */
  *(interval_timer_ptr + 0x2) = (counter & 0xFFFF);
  *(interval_timer_ptr + 0x3) = (counter >> 16) & 0xFFFF;
  /* start interval timer, enable its interrupts */
  *(interval_timer_ptr + 1) = 0x7; // STOP = 0, START = 1, CONT = 1, ITO = 1
  *(KEY_ptr + 2) = 0xF; /* write to the pushbutton interrupt mask register, and
  * set mask bits to 1 */
  NIOS2_WRITE_IENABLE( 0x3 ); /* set interrupt mask bits for levels 0 (interval timer)
  * and level 1 (pushbuttons) */
  NIOS2_WRITE_STATUS( 1 ); // enable Nios II interrupts


  initialization();

  while(1); // main program simply idles
}
