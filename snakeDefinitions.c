#include <stdlib.h>
#include <stdio.h>
short bodyColor = (short) 0b0000011111100000;
short headColor = (short) 0b1111100000000000;
const short foodColor = (short) 0b11111111111000000; //yellow
extern volatile int currentDirection;

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
struct Snake *head;

void init(){
	 head = malloc(sizeof(struct Snake));
	 //set up first node
	 struct Node *firstNode = malloc(sizeof(struct Node));
	 //set up starting positions and colors
	 firstNode->xPosition = (317/2) + 1;
	 firstNode->yPosition = (237/2) + 1;
	 firstNode->color = headColor;
	 firstNode->next = 0;
	 firstNode->previous = 0;
 	 head->firstNode = firstNode;

	 fillSquare(firstNode->xPosition-1, firstNode->xPosition+1, firstNode->yPosition-1, firstNode->yPosition+1, firstNode->color);
	 printf("Initialization complete\n");
}

/**
 * Function that handles inserting a link to the snake. Please note we do not wish to move the entire snake (list of nodes).
 * Insead, we just advance the head up one and then insert a new link behind the head of the snake.
 */
void insertLink(struct Snake *top){
	//INSERTING NEW GUY DIRECTLY AFTER HEAD. efficiency reasons
	struct Node *newNode = malloc(sizeof(struct Node));
	newNode->previous = top->firstNode; //new guy points back	1
	newNode->next = top->firstNode->next; //new guy says the next thing is the link after the firstNode 2
	if (newNode->next ==0){
		printf("Properly set first iteration\n");
	}
	if (top->firstNode->next != 0){
		top->firstNode->next->previous = newNode;// 3
	}
	top->firstNode->next = newNode; //old guy says the next thing is the new guy 4
	
	newNode->xPosition = top->firstNode->xPosition;
	newNode->yPosition = top->firstNode->yPosition;
	
	fillSquare(top->firstNode->xPosition-1, top->firstNode->xPosition+1, top->firstNode->yPosition-1, top->firstNode->yPosition+1, bodyColor); //color the old head position

	//can do preincrement / decrement for efficiency later on
	if (currentDirection == POS_X){
		top->firstNode->xPosition = (top->firstNode->xPosition + 2); 
	}else if (currentDirection == NEG_X){
		top->firstNode->xPosition = (top->firstNode->xPosition - 2);
	}else if (currentDirection == POS_Y){
		//NOTE A POSITIVE Y IS TECHNICALLY DOWN
		top->firstNode->yPosition = (top->firstNode->yPosition + 2);
	}else if (currentDirection == NEG_Y){
		//NOTE A NEGATIVE Y IS TECHNICALLY UP
		top->firstNode->yPosition = (top->firstNode->yPosition - 2);
	}
	fillSquare(top->firstNode->xPosition-1, top->firstNode->xPosition+1, top->firstNode->yPosition-1, top->firstNode->yPosition+1, headColor); //color the new head
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
	fillSquare(currentLink->xPosition-1, currentLink->xPosition+1, currentLink->yPosition-1, currentLink->yPosition+1, 0x0); //set the tail to be uncolored

	//advance position of tail to be where the head was
	currentLink->xPosition = top->firstNode->xPosition;
	currentLink->yPosition = top->firstNode->yPosition;
	
	//check to make sure we are not manipulating the head. I do not want to do these 
	//manipulations to the head as it makes it circular. I DO NOT WANT THE LIST TO BE CIRCULAR
	if (currentLink != top->firstNode){
		currentLink->previous->next = 0; //set the new tail
		currentLink->previous = top->firstNode; //set the 2nd position's previous to point back to firstNode
		currentLink->next = top->firstNode->next; //set the 2nd position to point to the third
		currentLink->next->previous = currentLink;
		top->firstNode->next = currentLink; //set the firstNode's next to point to the second position
	}
	
	//verify snake has more than 1 node for this color shift
	if (top->firstNode->next != 0){
		//recolor pixel at old head
		fillSquare(top->firstNode->xPosition-1, top->firstNode->xPosition+1, top->firstNode->yPosition-1, top->firstNode->yPosition+1, bodyColor); //color the old head position

	}
	//can do preincrement / decrement for efficiency later on
	if (currentDirection == POS_X){
		top->firstNode->xPosition = top->firstNode->xPosition + 2; 
	}else if (currentDirection == NEG_X){
		top->firstNode->xPosition = top->firstNode->xPosition - 2;
	}else if (currentDirection == POS_Y){
		//NOTE A POSITIVE Y IS TECHNICALLY DOWN
		top->firstNode->yPosition = top->firstNode->yPosition + 2;
	}else if (currentDirection == NEG_Y){
		//NOTE A NEGATIVE Y IS TECHNICALLY UP
		top->firstNode->yPosition = top->firstNode->yPosition - 2;
	}
	//draw the new head position
	fillSquare(top->firstNode->xPosition-1, top->firstNode->xPosition+1, top->firstNode->yPosition-1, top->firstNode->yPosition+1, headColor); //color the new head position
}

/**
 * Function for generating a 1x1 food pixel
 */
void generateFood(struct Snake *top){
	int conflict = 1;
	int foodXCoordinate;
	int foodYCoordinate;
	while (conflict){
		conflict = 0;
		//plus 1 is for wall offset
		foodXCoordinate = (rand() % 315) + 2;
		foodYCoordinate = (rand() % 235) + 2;

		//check for conflicts
		for (struct Node *temp = top->firstNode; temp->next != 0; temp = temp->next){
			if (temp->xPosition == foodXCoordinate && temp->yPosition == foodYCoordinate){
				//conflict 
				conflict = 1;
				break;
			}
		}
	}
	fillSquare(foodXCoordinate-1, foodXCoordinate+1, foodYCoordinate-1, foodYCoordinate+1, foodColor);

}


/**
 * Function for deleting all of the snake's dynamic memory.
 * Prventing leaks.
 
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
 */
