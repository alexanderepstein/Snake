#ifndef PROTOTYPES
	#define PROTOTYPES
	
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
	//function prototypes
	void initialization(void);
	int checktokillSnake(void);
	void checkForFoodCollision(void);
	void move(struct Snake*);
	void clearText(void);
	void setInfoBar(void);
	void setScore(void);
	void fillSquare(int,int,int,int,short);
	void buildWall(short);
	void finishGame(void);
	void VGA_text(int,int,char*);
	void clearscreen(void);
	void initSnake(void);
	void insertLink(struct Snake*);
	void generateFood(struct Snake*);
#endif

