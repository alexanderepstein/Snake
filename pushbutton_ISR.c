
extern volatile int scrollType, direction, pause;
/********************************************************************************
* Pushbutton - Interrupt Service Routine
*
* This routine checks which KEY has been pressed. It writes this value to the global
* variable KEY_PRESSED.
********************************************************************************/
void pushbutton_ISR( void ) {
/*volatile int * KEY_ptr = (int *) 0xFF200050;
int press;
press = *(KEY_ptr + 3); // read the pushbutton interrupt register
*(KEY_ptr + 3) = press; // clear the interrupt
if (press & 0x1) // KEY0
{
	if (pause ==0)
	{
		pause = 1;
	}
	else
	{
		pause = 0;
	}
}
else if (press & 0x2) {// KEY1
	if (scrollType == 1){
		scrollType = 0;
	}else {
		scrollType = 1;
	}
}
else if (press & 0x4) //KEY 2
{
  direction = 0;
}
else if(press & 0x8) //KEY 3
{
  direction = 1;
}
*/
return;
}
