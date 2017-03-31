#include "stdio.h"

int temp;
extern volatile int yPos, currentDirection, start, pushButtonThread;
/********************************************************************************
* Interval timer interrupt service routine
********************************************************************************/
volatile int timerThread = 0;
extern volatile struct Snake *head;

int counter = 0;
void interval_timer_isr(){

	volatile int * interval_timer_ptr = (int *) 0xFF202000; // interval timer base address
	*(interval_timer_ptr) = 0; // clear the interrupt
	if (!pushButtonThread && !timerThread)
	{

		timerThread =1;
		if (start)
		{
		  //insertLink(head);
		  move(head);
		  //recolorHead(head);
		}

		timerThread = 0;
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
