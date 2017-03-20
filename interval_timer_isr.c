#include "stdio.h"

int temp;
extern volatile int yPos, direction;
/********************************************************************************
* Interval timer interrupt service routine
********************************************************************************/

extern volatile struct Snake *head;

void interval_timer_isr(){

	volatile int * interval_timer_ptr = (int *) 0xFF202000; // interval timer base address
	*(interval_timer_ptr) = 0; // clear the interrupt

	//while(1){
	
		clearscreen();
		int x_max, y_max, x_start, y_start;
		
		/* Draw an orange horzontal line */
		for (x_max = 0; x_max < 319; x_max = x_max + 1){
			//blue is 248, 3968 is bright green
			//so last 5 bits red, middle 6 green, first 5 blue. Gotta do this shit in binary
			drawpixel(x_max, yPos, 0b1000000000011111);
		}
		yPos = yPos + direction; //increment vertical position
		if (yPos == 239 || yPos == 0){
			direction = direction * -1; //invert direction
		}
	//}


}
