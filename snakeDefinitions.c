#include <stdlib.h>


struct Node{
	int xPosition;
	int yPosition;
	struct Node *next;
	struct Node *previous;
	short color;
};

struct Snake{
	struct Node *head;
};

//setting up head here
struct Snake *head;

void initi(){
	 head = malloc(sizeof(struct Snake));
}

/**
 * Function that handles inserting a link to the snake. Please note we do not wish to move the entire snake (list of nodes).
 * Insead, we just advance the head up one and then insert a new link behind the head of the snake.
 */
void insertLink(struct Snake *currentLink){
	//INSERTING NEW GUY DIRECTLY AFTER HEAD. efficiency reasons
	struct Node *newNode = malloc(sizeof(struct Node));
	newNode->previous = currentLink->head; //new guy points back
	newNode->next = currentLink->head->next; //new guy says the next thing is the link after the head
	currentLink->head->next = newNode; //old guy says the next thing is the new guy
	
	newNode->xPosition = currentLink->head->xPosition;
	newNode->yPosition = currentLink->head->yPosition;
	
	//can do preincrement / decrement for efficiency later on
	if (direction == POS_X){
		currentLink->head->xPosition = currentLink->head->xPosition + 1; 
	}else if (direction == NEG_X){
		currentLink->head->xPosition = currentLink->head->xPosition - 1;
	}else if (direction == POS_Y){
		//NOTE A POSITIVE Y IS TECHNICALLY DOWN
		currentLink->head->yPosition = currentLink->head->yPosition + 1;
	}else if (direction == NEG_Y){
		//NOTE A NEGATIVE Y IS TECHNICALLY UP
		currentLink->head->yPosition = currentLink->head->yPosition - 1;
	}
}

/**
 * Function responsible for advancing the snakes position. Please note we do not wish to move the entire snake (list of nodes).
 * Insead, we advance the head up one then slide the tail up behind the head. Effectively the head moves up one and last link becomes the new second 
 * link while the rest of the snake remains stationary.
 */
void move(struct Snake *top){
	struct Node *currentLink = top->head;
	while (currentLink->next !=0){
		currentLink = currentLink->next;
	}
	//at this point I have reached the end of the list
	currentLink->xPosition = top->head->xPosition;
	currentLink->yPosition = top->head->yPosition;
	
	currentLink->previous->next = 0; //set the new tail
	currentLink->next = top->head->next; //set the 2nd position to point to the third
	currentLink->previous = top->head; //set the 2nd position's previous to point back to head
	top->head->next = currentLink; //set the head's next to point to the second position
	
	//can do preincrement / decrement for efficiency later on
	if (direction == POS_X){
		top->head->xPosition = top->head->xPosition + 1; 
	}else if (direction == NEG_X){
		top->head->xPosition = top->head->xPosition - 1;
	}else if (direction == POS_Y){
		//NOTE A POSITIVE Y IS TECHNICALLY DOWN
		top->head->yPosition = top->head->yPosition + 1;
	}else if (direction == NEG_Y){
		//NOTE A NEGATIVE Y IS TECHNICALLY UP
		top->head->yPosition = top->head->yPosition - 1;
	}
}
