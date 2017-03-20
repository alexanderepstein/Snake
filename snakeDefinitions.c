
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

//setting up head here
volatile struct Snake *head = malloc(sizeof(Snake);



void insertLink(struct Snake *currentLink){
	/*while (currentLink->next !=0){
		currentLink = currentLink->next;
	}*/
	//at this point I've reached the end so I add a new guy.
	//ACTUALLY INSERTING NEW GUY DIRECTLY AFTER HEAD
	struct Node *newNode = malloc(sizeof(Node));
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

void move(struct Snake *currentLink){
	while (currentLink->next !=0){
		currentLink = currentLink->next;
	}
	//at this point I have reached the end of the list
	currentLink->xPosition = head->xPosition;
	currentLink->yPosition = head->yPosition;
	
	currentLink->previous->next = 0; //set the new tail
	currentLink->next = head->next; //set the 2nd position to point to the third
	currentLink->previous = head; //set the 2nd position's previous to point back to head
	head->next = currentLink; //set the head's next to point to the second position
	
	//can do preincrement / decrement for efficiency later on
	if (direction == POS_X){
		head->xPosition = head->xPosition + 1; 
	}else if (direction == NEG_X){
		head->xPosition = head->xPosition - 1;
	}else if (direction == POS_Y){
		//NOTE A POSITIVE Y IS TECHNICALLY DOWN
		head->yPosition = head->yPosition + 1;
	}else if (direction == NEG_Y){
		//NOTE A NEGATIVE Y IS TECHNICALLY UP
		head->yPosition = head->yPosition - 1;
	}
}
