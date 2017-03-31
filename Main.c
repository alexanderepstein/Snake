#include "nios2_ctrl_reg_macros.h"

/* key_pressed and pattern are written by interrupt service routines; we have to declare
* these as volatile to avoid the compiler caching their values in registers */

volatile int firstPattern = 0b00000000000000000000000000000000; // pattern for HEX displays
volatile int secondPattern = 0b00000000000000000000000000000000;
volatile int scrollType = 0;
volatile int lastScrollType = 0;
//volatile int direction = 1;
volatile int direction = -1;
volatile int yPos = 120;
volatile int lastDirection =0;
volatile int pause = 0;
/********************************************************************************
* This program demonstrates use of interrupts in the DE0-CV Computer. It first starts the
* interval timer with 33 msec timeouts, and then enables interrupts from the interval timer
* and pushbutton KEYs
*
* The interrupt service routine for the Altera interval timer displays a pattern on the HEX3-0
* displays, and rotates this pattern either left or right:
* KEY[0]: loads a new pattern from the SW switches
* KEY[1]: rotates the displayed pattern to the right
* KEY[2]: rotates the displayed pattern to the left
* KEY[3]: stops the rotation
********************************************************************************/
int main(void){
/* Declare volatile pointers to I/O registers (volatile means that IO load and store instructions
* will be used to access these pointer locations instead of regular memory loads and stores) */
volatile int * interval_timer_ptr = (int *) 0xFF202000; // interval timer base address
volatile int * KEY_ptr = (int *) 0xFF200050; // pushbutton KEY address
/* set the interval timer period for scrolling the HEX displays */
int counter = 60000000; // 1/(100 MHz) × (5000000) = 50 msec
*(interval_timer_ptr + 0x2) = (counter & 0xFFFF);
*(interval_timer_ptr + 0x3) = (counter >> 16) & 0xFFFF;
/* start interval timer, enable its interrupts */
*(interval_timer_ptr + 1) = 0x7; // STOP = 0, START = 1, CONT = 1, ITO = 1
*(KEY_ptr + 2) = 0xF; /* write to the pushbutton interrupt mask register, and
* set mask bits to 1 */
NIOS2_WRITE_IENABLE( 0x3 ); /* set interrupt mask bits for levels 0 (interval timer)
* and level 1 (pushbuttons) */
NIOS2_WRITE_STATUS( 1 ); // enable Nios II interrupts
clearscreen();
buildWall(0b1111100000000000);
init();
while(1); // main program simply idles
}
