#include "stdio.h"


extern volatile int yPos, currentDirection, start, pushButtonThread;
/********************************************************************************
* Interval timer interrupt service routine
********************************************************************************/
volatile int timerThread = 0;
extern volatile struct Snake *head;
extern volatile int playAgain, welcome;



void interval_timer_isr(){

	volatile int * interval_timer_ptr = (int *) 0xFF202000; // interval timer base address
	*(interval_timer_ptr) = 0; // clear the interrupt
	if (!pushButtonThread && !timerThread) //check if timer and push button threads are not running
	{

		timerThread =1; //set timer thread to running
		
		//Called when game needs to be replayed
		if (playAgain && start){
			playAgain = 0;
			initialization();
		}
		
		if (start && head!=0 && !playAgain && welcome == 0) //check if the game has started
		{
		  //insertLink(head);
		  if (!checktokillSnake()){
			checkForFoodCollision();  
			move(head); //move the snake
		  }
		 
		}



		timerThread = 0; //set the timer thread to not running
		return;

	
	}
}
