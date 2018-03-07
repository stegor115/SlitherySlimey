#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "SDL.h"

class Game {
public:
	//Constructor/Destructor
	Game();
	~Game();

	void init(const char* title, int width, int height); //Game window
	void handleEvents();
	void update();
	bool running() { return isRunning; };
	void clean();
	Uint32 timer();
	//Food
	bool eat();
	void spawnFood();

private:
	bool isRunning = false;
	int cnt = 0;
	SDL_Window *window;
	SDL_Renderer *renderer;
	int windowWidth;
	int windowHeight;
	//Snake related ------------------
	SDL_Rect snakeHead;
	int bodyLength = 1; //Starts at 1 due to the head
	//FPS
	Uint32 startTime;
	//Direction of snake
	bool north = false;
	bool south = false;
	bool east = true; //Snake starts moving east
	bool west = false;

	//Food
	SDL_Rect food;
};