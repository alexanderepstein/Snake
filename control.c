extern struct Snake *head;
int currentXvalueOfHead = head->firstNode->xPosition;
int currentYvalueOfHead = head->firstNode->yPosition;

checktokillSnake(currentXvalueOfHead, currentYvalueOfHead);

void checktokillSnake(int x, int y){
	
	if(x<=0 || x>=318 || y<=0 || y>=239){
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
