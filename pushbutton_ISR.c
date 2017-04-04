#include <stdio.h>
#if !defined(NEG_X) || !defined(POS_X) || !defined(NEG_Y) || !defined(POS_Y)
	#define POS_X 1
	#define NEG_X 2
	#define POS_Y 3
	#define NEG_Y 4
#endif
volatile int currentDirection;
volatile int pushButtonThread = 0;
extern volatile struct Snake *head;
extern volatile int start, timerThread, welcome;
int press;



/********************************************************************************
* Pushbutton - Interrupt Service Routine
*
* This routine checks which KEY has been pressed. It writes this value to the global
* variable KEY_PRESSED.
********************************************************************************/
void pushbutton_ISR( void ) {
	
	if (welcome ==1)
	{
		clearText();
		setInfoBar();
		welcome = 0;
		return;
	}
start =1;
volatile int * KEY_ptr = (int *) 0xFF200050;

press= *(KEY_ptr + 3); // read the pushbutton interrupt register
*(KEY_ptr + 3) = press; // clear the interrupt



if (!timerThread && !pushButtonThread) //check if the timer isr is not running along with pushButtonThread 
{
	pushButtonThread = 1; //set the push button isr thread to be running


/*
The large conditional block determine the button was pressed and based on the
current direction determines whether or not you can go the desired direction
if you can the direction will be changed, if not the isr will essentially do nothing
*/


	if (press & 0x1) // KEY0
	{
		if (currentDirection != 2)
		{
		  currentDirection = 1;
		  printf("First button \n");

	  }
	}
	else if (press & 0x2)
	{
		if (currentDirection!= 1)
		{
		  currentDirection = 2;
		  printf("Second button \n");

	  }
	}
	else if (press & 0x4) //KEY 2
	{
		if (currentDirection!= 4)
		{
		 currentDirection = 3;
		 printf("Third button \n");

	  }
	}
	else if(press & 0x8) //KEY 3
	{
		if (currentDirection!= 3)
		{
		currentDirection = 4;
		printf("Fourth button \n");
	  }

	}
	pushButtonThread = 0; //set the push button isr thread to not running
}
return;

}
