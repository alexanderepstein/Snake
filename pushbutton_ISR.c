#include <stdio.h>
#if !defined(NEG_X) || !defined(POS_X) || !defined(NEG_Y) || !defined(POS_Y)
	#define POS_X 1
	#define NEG_X 2
	#define POS_Y 3
	#define NEG_Y 4
#endif
volatile int currentDirection;
extern volatile struct Snake *head;
extern volatile int start;

/********************************************************************************
* Pushbutton - Interrupt Service Routine
*
* This routine checks which KEY has been pressed. It writes this value to the global
* variable KEY_PRESSED.
********************************************************************************/
void pushbutton_ISR( void ) {
volatile int * KEY_ptr = (int *) 0xFF200050;
int press;
start =1;
press = *(KEY_ptr + 3); // read the pushbutton interrupt register
*(KEY_ptr + 3) = press; // clear the interrupt

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
	//insertLink(head);

  }

}

return;
}
