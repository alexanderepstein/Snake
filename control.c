extern struct Snake *head;
nodex = head->head->xPosition;
nodey = head->head->yPosition;

checktokillSnake(nodex, nodey);

void checktokillSnake(int x, int y){
	
	if(x<=0 || x>=319 || y<=0 || y>=239){
		//kill snake
	}
	
	int currentXvalueOfHead; 
	int currentYvalueOfHead;


	//get the x and y value of the snake head
	currentXvalueOfHead = head->firstNode->xPosition;
	currentYvalueOfHead = head->firstNode->yPosition;


	/*to advance a list
	set up node*/
	//                                            list still has more stuff.     //advance where we are looking in the list
	for (struct node = head->firstNode->next; node->next != 0; node = node->next){
		//instantiate node as next thing after head
		
		int currentXvalueOfBody;
		int currentYvalueOfBody;

		//get x and y value of the current node
		currentXvalueOfBody = node->xPosition;
		currentYvalueOfBody = node->yPosition;	
			
		//if the current node position equals the current positon of the snakes head, kill the snake
		(if currentXvalueOfBody==currentXvalueOfHead || currentYvalueOfBody==currentYvalueOfHead){
			//kill snake
		}
	}
}
