#include <stdlib.h>

short color = 0b0000011111100000;
extern int direction;

#if !defined(NEG_X) || !defined(POS_X) || !defined(NEG_Y) || !defined(POS_Y)
	#define POS_X 1
	#define NEG_X 2
	#define POS_Y 3
	#define NEG_Y 4
#endif
struct Node{
	int xPosition;
	int yPosition;
	struct Node *next;
	struct Node *previous;
	short color;
};

struct Snake{
	struct Node *firstNode;
};

//setting up head here
volatile struct Snake *head;

void init(){
	 head = malloc(sizeof(struct Snake));
	 //set up first node
	 struct Node *firstNode = malloc(sizeof(struct Node));
	 //set up starting positions and colors
	 firstNode->xPosition = 50;
	 firstNode->yPosition = 50;
	 firstNode->color = color;
	 head->firstNode = firstNode;
}

/**
 * Function that handles inserting a link to the snake. Please note we do not wish to move the entire snake (list of nodes).
 * Insead, we just advance the head up one and then insert a new link behind the head of the snake.
 */
void insertLink(struct Snake *currentLink){
	//INSERTING NEW GUY DIRECTLY AFTER HEAD. efficiency reasons
	struct Node *newNode = malloc(sizeof(struct Node));
	newNode->previous = currentLink->firstNode; //new guy points back
	newNode->next = currentLink->firstNode->next; //new guy says the next thing is the link after the firstNode
	currentLink->firstNode->next = newNode; //old guy says the next thing is the new guy
	
	newNode->xPosition = currentLink->firstNode->xPosition;
	newNode->yPosition = currentLink->firstNode->yPosition;
	
	//can do preincrement / decrement for efficiency later on
	if (direction == POS_X){
		currentLink->firstNode->xPosition = currentLink->firstNode->xPosition + 1; 
	}else if (direction == NEG_X){
		currentLink->firstNode->xPosition = currentLink->firstNode->xPosition - 1;
	}else if (direction == POS_Y){
		//NOTE A POSITIVE Y IS TECHNICALLY DOWN
		currentLink->firstNode->yPosition = currentLink->firstNode->yPosition + 1;
	}else if (direction == NEG_Y){
		//NOTE A NEGATIVE Y IS TECHNICALLY UP
		currentLink->firstNode->yPosition = currentLink->firstNode->yPosition - 1;
	}
	drawpixel(currentLink->firstNode->xPosition, currentLink->firstNode->yPosition, color);
}

/**
 * Function responsible for advancing the snakes position. Please note we do not wish to move the entire snake (list of nodes).
 * Insead, we advance the head up one then slide the tail up behind the head. Effectively the head moves up one and last link becomes the new second 
 * link while the rest of the snake remains stationary.
 */
void move(struct Snake *top){
	struct Node *currentLink = top->firstNode;
	while (currentLink->next !=0){
		currentLink = currentLink->next;
	}
	//at this point I have reached the end of the list
	drawpixel(currentLink->xPosition, currentLink->yPosition, 0x0); //set the tail to be uncolored
	currentLink->xPosition = top->firstNode->xPosition;
	currentLink->yPosition = top->firstNode->yPosition;
	
	currentLink->previous->next = 0; //set the new tail
	currentLink->next = top->firstNode->next; //set the 2nd position to point to the third
	currentLink->previous = top->firstNode; //set the 2nd position's previous to point back to firstNode
	top->firstNode->next = currentLink; //set the firstNode's next to point to the second position
	
	//can do preincrement / decrement for efficiency later on
	if (direction == POS_X){
		top->firstNode->xPosition = top->firstNode->xPosition + 1; 
	}else if (direction == NEG_X){
		top->firstNode->xPosition = top->firstNode->xPosition - 1;
	}else if (direction == POS_Y){
		//NOTE A POSITIVE Y IS TECHNICALLY DOWN
		top->firstNode->yPosition = top->firstNode->yPosition + 1;
	}else if (direction == NEG_Y){
		//NOTE A NEGATIVE Y IS TECHNICALLY UP
		top->firstNode->yPosition = top->firstNode->yPosition - 1;
	}
	drawpixel(top->firstNode->xPosition, top->firstNode->yPosition, 0b0000011111100000, color); //color the new position
}

/**
 * Function for deleting all of the snake's dynamic memory.
 * Prventing leaks.
 */
 void deleteSnake(struct Snake *top){
	 struct Node *currentLink = top->firstNode;
	 //get to the end of the list
	 while (currentLink->next !=0){
		currentLink = currentLink->next;
	}
	struct Node *temp; //temporay pointer that will store an additional link to prevent orphaning
	
	//check that there is something before it
	while(currentLink->previous !=0){
		temp = currentLink; //set temporary pointer
		temp = currentLink->previous; //go back one
		free(currentLink); //delete the current one
		currentLink = temp; //slide our tracking variable 
	}
	free(currentLink); //last link
	free(top); //dump the pointer at the head of the snake
 }
