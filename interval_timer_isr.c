#include "stdio.h"



int temp;
extern volatile int yPos, direction;
/********************************************************************************
* Interval timer interrupt service routine
********************************************************************************/

volatile struct Snake{
	struct Node head;
	
};

volatile struct Node{
	int xPosition;
	int yPosition;
	struct Node next;
	struct Node previous;
	short color;
};

void insertLink(struct Snake currentLink){
	currentLink = head;
	/*while (currentLink->next !=0){
		currentLink = currentLink->next;
	}*/
	//at this point I've reached the end so I add a new guy.
	//ACTUALLY INSERTING NEW GUY DIRECTLY AFTER HEAD
	struct Node newNode = malloc(sizeof(Node));
	newNode->previous = currentLink; //new guy points back
	newNode->next = currentLink->next; //new guy says the next thing is the link after the head
	currentLink->next = newNode; //old guy says the next thing is the new guy
	
	newNode->xPosition = currentLink->xPosition;
	newNode->yPosition = currentLink->yPosition;
	
	//can do preincrement / decrement for efficiency later on
	if (direction == POS_X){
		currentLink->xPosition = currentLink->xPosition + 1; 
	}else if (direction == NEG_X){
		currentLink->xPosition = currentLink->xPosition - 1;
	}else if (direction == POS_Y){
		//NOTE A POSITIVE Y IS TECHNICALLY DOWN
		currentLink->yPosition = currentLink->yPosition + 1;
	}else if (direction == NEG_Y){
		//NOTE A NEGATIVE Y IS TECHNICALLY UP
		currentLink->yPosition = currentLink->yPosition - 1;
	}
	
}

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
