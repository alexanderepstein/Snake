#include "stdio.h"


extern volatile int yPos, currentDirection, start, pushButtonThread;
/********************************************************************************
* Interval timer interrupt service routine
********************************************************************************/
volatile int timerThread = 0;
extern volatile struct Snake *head;
int score = 900;
int counter = 0;

void interval_timer_isr(){

	volatile int * interval_timer_ptr = (int *) 0xFF202000; // interval timer base address
	*(interval_timer_ptr) = 0; // clear the interrupt
	if (!pushButtonThread && !timerThread) //check if timer and push button threads are not running
	{

		timerThread =1; //set timer thread to running
		if (start) //check if the game has started
		{
		  //insertLink(head);
		  move(head); //move the snake;
		  drawScore(score, 67, 2);
		  score--;
		  ++counter;
		  if (counter >=10){
			counter = 0;
			drawScore(score, 67, 2);
			score--;
		  }
		  //recolorHead(head);
		}

		timerThread = 0; //set the timer thread to not running
		return;

	/*
	if (start ==1)
	{
		move(head);
	}
	if (counter == 10){
		insertLink(head); //adding another link
	}*/
	//while(1){

	//	clearscreen();

	}
}
