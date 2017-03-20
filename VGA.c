//#include <stdio.h>
#include "nios2_ctrl_reg_macros.h"

/*
* 1. Draw a horizontal line in the center of the screen
  2. Move the line up by an increment of 1
  3. When the upper limit of the pixel buffer is detected, reverse the direction of line movement (down) until the bottom limit is detected. Reverse and repeat loop forever.
  4. Time between line position updates is 250 ms
  5. Use interval timer to generate the delay
*/


/* these globals are written by interrupt service routines; we have to declare 
 * these as volatile to avoid the compiler caching their values in registers */
extern volatile char byte1, byte2;			/* modified by PS/2 interrupt service routine */
extern volatile int timeout;					// used to synchronize with the timer

/*Color a pixel */
/*void drawpixel(int x_vga, int y_vga, short color){
	volatile char *pixel_address = (volatile char*) (0x08000000 + (y_vga <<7) + (x_vga));
	*pixel_address = color;
}*/

/* For DE0-CV
*
*/

void drawpixel(int x_vga, int y_vga, short color){
	volatile short *pixel_address = (volatile short*)(0x08000000 + (y_vga<<10) + (x_vga<<1)); 
    *pixel_address = color;
}



/* Paint the screen BLACK 
* DE0 Limits x= 79,  y=59
* DE0-CV	 x= 319, y=239
*/

void clearscreen (){
	int x_vga, y_vga;
	for (x_vga = 0; x_vga <=319; x_vga = x_vga + 1){
		for (y_vga = 0; y_vga <=239; y_vga = y_vga + 1){
			drawpixel(x_vga, y_vga, 0x0);
		}
	}
}

/* Draw a single character on the screen */

/*void drawcharacter(int x_char, int y_char, char mychar){
	volatile char* character_buffer = (char *) (0x09000000 + (y_char <<7) + x_char);
	*character_buffer = mychar;
}*/
volatile int direction = -1;
volatile int yPos = 120;
int main(){	
	
	/* Declare volatile pointers to I/O registers (volatile means that IO load and store instructions
	* will be used to access these pointer locations instead of regular memory loads and stores) */
	volatile int * interval_timer_ptr = (int *) 0xFF202000; // interval timer base address
	//volatile int * KEY_ptr = (int *) 0xFF200050; // pushbutton KEY address
	/* set the interval timer period for scrolling the HEX displays */
	int counter = 25000000; // (100 MHz) × (250ms)
	*(interval_timer_ptr + 0x2) = (counter & 0xFFFF);
	*(interval_timer_ptr + 0x3) = (counter >> 16) & 0xFFFF;
	/* start interval timer, enable its interrupts */
	*(interval_timer_ptr + 1) = 0x7; // STOP = 0, START = 1, CONT = 1, ITO = 1
	//*(KEY_ptr + 2) = 0xF; /* write to the pushbutton interrupt mask register, and
	//* set mask bits to 1 */
	NIOS2_WRITE_IENABLE( 0x3 ); /* set interrupt mask bits for levels 0 (interval timer) technically I only need the interval timer
	* and level 1 (pushbuttons) */
	NIOS2_WRITE_STATUS( 1 ); // enable Nios II interrupts
	while(1); // main program simply idles
	
	
	/*while(1){
	
		clearscreen();
		int x_max, y_max, x_start, y_start;
		
		/* Draw an orange horzontal line */
	/*	for (x_max = 0; x_max < 319; x_max = x_max + 1){
			drawpixel(x_max, yPos, 248);
		}
		yPos = yPos + direction;
		if (yPos == 239 || yPos == 0){
			direction = direction * -1;
		}
	}
	*/
//	return 0;
}