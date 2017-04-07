#if !PRINT
	#include <stdio.h>
	#define PRINT
#endif
#include "nios2_ctrl_reg_macros.h"
#if !PROTOTYPE
	#include "prototypes.h"
#endif
extern volatile int score;

#define ASCII_NUM_SHIFT 48
int Numbers[10] = {0b0111111,0b0000110,0b1011011,0b1001111,0b1100110,0b1101101,0b1111101,0b0000111,0b1111111,0b1100111};

volatile int * HEX3_HEX0_ptr = (int *) 0xFF200020;
extern short backgroundColor;
extern volatile int start, playAgain;

volatile int score = 0;
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
 * Function for drawing a filled in square. Each node will act as one of these
 */
void fillSquare(int x1, int x2, int y1, int y2, short pixel_color){
	int row, col;

	/* assume that the box coordinates are valid */
	for (row = y1; row <= y2; row++){
		//iterate by row
		col = x1;
		while (col <= x2){
			//fill vertically
			drawpixel(col,row,pixel_color);
			++col;
		}
	}
}

/**
  * Function for constructing the wall perimeters in the game. Snake dies upon collision with these.
  */
void buildWall(short color){
	/*for (int x =0; x <= 319; x++){
		for (int y =0; y <= 239; y++){
			if (x <= 0 || x >= 319 || y <= 0 || y >= 239){
				drawpixel(x,y,color);
			}
		}
	}*/
	//this is more efficient as it iterates through less entries
	for (int y =20; y < 239; y++){
		drawpixel(0,y,color);
		drawpixel(318,y,color);
	}
	for (int x =0; x < 319; x++){
		drawpixel(x,20,color);
		drawpixel(x,239,color);
	}
	printf("Walls are drawn\n");

}


/* Paint the screen BLACK
* DE0 Limits x= 79,  y=59
* DE0-CV	 x= 319, y=239
*/

void clearscreen (){
	int x_vga, y_vga;
	for (x_vga = 0; x_vga <=319; x_vga = x_vga + 1){
		for (y_vga = 0; y_vga <=239; y_vga = y_vga + 1){
			drawpixel(x_vga, y_vga, backgroundColor);
		}
	}
}

void clearText()
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
			*(character_buffer + offset) = 0x00;	// write to the character buffer
			//++offset;

		}
	}

}

//67,68,69
void drawScore(int x, int y){
	int ones = score%10; //only get first digit of score
	int tens = (score%100 - ones) / 10; //only get second digit of score
	int hundreds = (score%1000 - tens - ones) /100; //only get third digit of score

	//redundancy
	if (tens < 0){
		tens = 0;
	}
	if (hundreds < 0){
		hundreds = 0;
	}

	volatile char * character_buffer = (char *) 0x09000000;	// VGA character buffer
	int offset = (y << 7) + (x); //how its stored as address y gets shifted up 7.
	*(character_buffer + offset) = (unsigned char) (hundreds + ASCII_NUM_SHIFT);	//shift slides up our min to be 48 or the ASCII of 0
	*(character_buffer + offset + 1) = (unsigned char) (tens + ASCII_NUM_SHIFT);
	*(character_buffer + offset + 2) = (unsigned char) (ones + ASCII_NUM_SHIFT);
}

void finishGame(){
	start = 0;
	VGA_text(35,30, "You lost!");
	printf("Finishing game");
	playAgain = 1;
}

void setScore()
{
	int  b , c, d;
	int temp = score;
	b = temp / 100;
	temp = temp - b*100;
	c = temp / 10;
	d = temp - c*10;
	*HEX3_HEX0_ptr = (Numbers[b] << 16) | (Numbers[c] << 8) | Numbers[d];
	drawScore(67,2);
}