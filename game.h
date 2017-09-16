
struct Ball {
	unsigned char x;
	unsigned char y;
	char x_speed;
	char y_speed;
};

struct Block {
	unsigned char x1;
	unsigned char y1;
	unsigned char x2;
	unsigned char y2;
};

void GameEngine(void);
void SetupGameEnvironment(void);
void Delay(unsigned int);
