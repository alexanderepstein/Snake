extern struct Snake *head;
int currentXvalueOfHead = head->firstNode->xPosition;
int currentYvalueOfHead = head->firstNode->yPosition;

checktokillSnake(currentXvalueOfHead, currentYvalueOfHead);
checkForFoodCollision(currentXvalueOfHead, currentYvalueOfHead);

void checktokillSnake(int x, int y){
	
	if(x<=1 || x>=317 || y<=21 || y>=238){
		//kill snake
		deleteSnake(head);
		break;
	}

	/*to advance a list
	set up node*/
	//                                            list still has more stuff.     //advance where we are looking in the list
	for (struct Node node = head->firstNode->next; node->next != 0; node = node->next){
		//instantiate node as next thing after head

		//get x and y value of the current node
		int currentXvalueOfBody = node->xPosition;
		int currentYvalueOfBody = node->yPosition;	
			
		//if the current node position equals the current positon of the snakes head, kill the snake
		if (currentXvalueOfBody==currentXvalueOfHead || currentYvalueOfBody==currentYvalueOfHead){
			//kill snake
			deleteSnake(head);
			break;
		}
	}
}

void checkForFoodCollision(int xMiddleOfHead, int yMiddleOfHead, int foodXMiddle, int foodYMiddle){
	
	//check to see if any of the x values of the head (xmiddle -1 through xmiddle+1) equal any x values of the food
	for(int i=xMiddleOfHead-1; i<=xMiddleOfHead+1; i++){
		if(i==foodXMiddle-1 || i==foodXMiddle || i==foodXMiddle+1){
			//add link
			//update score
		}
	}
	
	//same for y values
	for(int i=yMiddleOfHead-1; i<=yMiddleOfHead+1; i++){
		if(i==foodYMiddle-1 || i==foodYMiddle || i==foodYMiddle+1){
			//add link
			//update score
		}
	}
	
	
	

