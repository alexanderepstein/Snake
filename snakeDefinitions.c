#include <stdlib.h>
#if !PRINT
	#include <stdio.h>
	#define PRINT
#endif

#if !PROTOTYPE
	#include "prototypes.h"
#endif


int checkWallCollision();

const short bodyColor = (short) 0b0000011111100000;
const short headColor = (short) 0b1111100000000000;
const short foodColor = (short) 0b11111111111000000; //yellow
const short backgroundColor = (short) (0b0000000000000111); //sorta blueish
extern const short wallColor;

extern volatile int currentDirection;

int foodXCoordinate;
int foodYCoordinate;
extern volatile int counter;
extern volatile int score;
#if !defined(NEG_X) || !defined(POS_X) || !defined(NEG_Y) || !defined(POS_Y)
	#define POS_X 1
	#define NEG_X 2
	#define POS_Y 3
	#define NEG_Y 4
#endif


//setting up head here
struct Snake *head;

void initSnake(){
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
	 printf("Snake Initialized \n");
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
		top->firstNode->xPosition = (top->firstNode->xPosition + 3);
	}else if (currentDirection == NEG_X){
		top->firstNode->xPosition = (top->firstNode->xPosition - 3);
	}else if (currentDirection == POS_Y){
		//NOTE A POSITIVE Y IS TECHNICALLY DOWN
		top->firstNode->yPosition = (top->firstNode->yPosition + 3);
	}else if (currentDirection == NEG_Y){
		top->firstNode->yPosition = (top->firstNode->yPosition -3);
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
	fillSquare(currentLink->xPosition-1, currentLink->xPosition+1, currentLink->yPosition-1, currentLink->yPosition+1, backgroundColor); //set the tail to be uncolored

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
		top->firstNode->xPosition = top->firstNode->xPosition + 3;
	}else if (currentDirection == NEG_X){
		top->firstNode->xPosition = top->firstNode->xPosition - 3;
	}else if (currentDirection == POS_Y){
		//NOTE A POSITIVE Y IS TECHNICALLY DOWN
		top->firstNode->yPosition = top->firstNode->yPosition + 3;
	}else if (currentDirection == NEG_Y){
		//NOTE A NEGATIVE Y IS TECHNICALLY UP
		top->firstNode->yPosition = top->firstNode->yPosition - 3;
	}
	//draw the new head position
	fillSquare(top->firstNode->xPosition-1, top->firstNode->xPosition+1, top->firstNode->yPosition-1, top->firstNode->yPosition+1, headColor); //color the new head position
}

/**
 * Function for generating a 1x1 food pixel
 */
void generateFood(struct Snake *top){
	printf("Food is redrawn\n");
	int conflict = 1;
	while (conflict){
		conflict = 0;
		//plus 2 is for wall offset. Generate food particle fully within wall boundaries.
		foodXCoordinate = (rand() % 315) + 1;
		foodYCoordinate = (rand() % 215) + 22;

		//check for conflicts
		for (struct Node *temp = top->firstNode; temp->next != 0; temp = temp->next){
			if ((temp->xPosition >= foodXCoordinate-2) && (temp->xPosition <= foodXCoordinate+2) && (temp->yPosition >= foodYCoordinate-2) && (temp->yPosition <= foodYCoordinate+2)){
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
*/
 void deleteSnake(struct Snake *top){
	 printf("Deleting snake\n");
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
		//fillSquare(currentLink->xPosition-1, currentLink->xPosition+1, currentLink->yPosition-1, currentLink->yPosition+1, backgroundColor); //set pixels back to regular
		currentLink->next = 0;
		currentLink->previous = 0;
		//Dave you might want the snake to stay
		free(currentLink); //delete the current one
		currentLink = temp; //slide our tracking variable
	}

	//If I still want the head DO NOT EXECUTE THIS. Forcibly dumping all pointer references as C can retain these after I free the memory
	//fillSquare(currentLink->xPosition-1, currentLink->xPosition+1, currentLink->yPosition-1, currentLink->yPosition+1, backgroundColor); //set pixels back to regular
	currentLink->next = 0;
	currentLink->previous = 0;
	top->firstNode->next = 0;
	top->firstNode->previous =0;
	free(top->firstNode);
	top->firstNode = 0;
	currentLink->previous = 0;
	//Dave you might want the snake to stay
	free(currentLink); //last link
	free(top); //dump the pointer at the head of the snake
	printf("Game Complete\n");
	buildWall(wallColor); //fix hole in the wall made by snake colliding and drawing over

	finishGame();
 }



int checktokillSnake(){
	//redundancy for faults
	if (head == 0 || head->firstNode == 0){
		return 1; //shit doesnt exist somthing wrong
	}

	int currentXvalueOfHead = head->firstNode->xPosition;
	int currentYvalueOfHead = head->firstNode->yPosition;
	if(checkWallCollision()){
		//ie something has happened
		return 1;
	}
	/*to advance a list
	set up node*/
	//                                            list still has more stuff.     //advance where we are looking in the list

	//only have head exit
	if (head->firstNode->next==0 || head->firstNode == 0 || head == 0){
		return 0; //no fault
	}
	for (struct Node *node = head->firstNode->next; node->next != 0; node = node->next){
		//instantiate node as next thing after head
		//get x and y value of the current node
		int currentXvalueOfBody = node->xPosition;
		int currentYvalueOfBody = node->yPosition;

		//if the current node position equals the current positon of the snakes head, kill the snake
		if ((currentXvalueOfBody >= currentXvalueOfHead -2) && (currentXvalueOfBody <= currentXvalueOfHead +2) && (currentYvalueOfBody>=currentYvalueOfHead-2) && (currentYvalueOfBody<=currentYvalueOfHead+2)) {
			//kill snake
			deleteSnake(head);
			return 1; //colllsion
		}
	}
	return 0;
}

void checkForFoodCollision(){
	struct Node *top = head->firstNode;
	int xMiddleOfHead = top->xPosition;
	int yMiddleOfHead = top->yPosition;
	//check 5x5 box (really 3x3 but it doesnt run properly consistently)
	if ((xMiddleOfHead >= foodXCoordinate-2) && (xMiddleOfHead <= foodXCoordinate+2) && (yMiddleOfHead >= foodYCoordinate-2) && (yMiddleOfHead <= foodYCoordinate+2)){
		printf("Food collision\n");
		//collision with food has occured
		score++;
		fillSquare(foodXCoordinate-1, foodXCoordinate+1, foodYCoordinate-1, foodYCoordinate+1, backgroundColor);
		insertLink(head);
		generateFood(head);
		//drawScore(67,2);
		setScore();
		if (score%5 == 0)
		{
		counter = counter - counter/10;
	  }
		volatile int * interval_timer_ptr = (int *) 0xFF202000; // interval timer base address
		*(interval_timer_ptr + 0x2) = (counter & 0xFFFF);
		*(interval_timer_ptr + 0x3) = (counter >> 16) & 0xFFFF;
		/* start interval timer, enable its interrupts */
		*(interval_timer_ptr + 1) = 0x7; // STOP = 0, START = 1, CONT = 1, ITO = 1
	}

}

int checkWallCollision(){
	if (head == 0 || head->firstNode == 0){
		return 1;//head is null some fault exit
	}

	if(head->firstNode->xPosition<=1 || head->firstNode->xPosition>=317 || head->firstNode->yPosition<=21 || head->firstNode->yPosition>=238){
		//kill snake
		deleteSnake(head);
		return 1;
	}else {
		return 0;
	}
}
