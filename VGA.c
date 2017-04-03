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
extern volatile struct Snake *head;
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
	//TODO double buffer
}



/****************************************************************************************
 * Subroutine to send a string of text to the VGA monitor
****************************************************************************************/
void VGA_text(int x, int y, char * text_ptr){
	int offset;
  	volatile char * character_buffer = (char *) 0x09000000;	// VGA character buffer

	/* assume that the text string fits on one line */
	offset = (y << 7) + (x); //how its stored as address y gets shifted up 7.
	while ( *(text_ptr) ){
		//while text has stuff
		*(character_buffer + offset) = *(text_ptr);	// write to the character buffer
		++text_ptr;
		++offset;
	}
}


/**
  * Function for constructing the wall perimeters in the game. Snake dies upon collision with these.
  */
void buildWall(short color){
	for (int x =0; x <= 319; x++){
		for (int y =0; y <= 239; y++){
			if (x == 0 || x == 319 || y ==0 || y == 239){
				drawpixel(x,y,color);
			}
		}
	}
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

void clearTest()
{
	volatile char * character_buffer = (char *) 0x09000000;	// VGA character buffer
	for (int i = 0;i <80;i++)
	{
		for(int j=0;j<60;j++)
		{
			int offset;

			/* assume that the text string fits on one line */
			offset = (j << 7) + (i); //how its stored as address y gets shifted up 7.

				//while text has stuff
			*(character_buffer + offset) = 0;	// write to the character buffer
			//++offset;

		}
	}

}

/* Draw a single character on the screen */

/*void drawcharacter(int x_char, int y_char, char mychar){
	volatile char* character_buffer = (char *) (0x09000000 + (y_char <<7) + x_char);
	*character_buffer = mychar;
}*/


void initialization()
{
	clearscreen();
	clearTest();
	char snakeText[10] = "Snake\0";
	char scoreText[10] = "Score\0";

	VGA_text(39,2,snakeText);
	VGA_text(60, 2,scoreText);
	buildWall(0b1111100000000000);
  init();
	generateFood(head);

}
