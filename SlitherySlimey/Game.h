#include <iostream>
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
	void render();
	void clean();
	Uint32 time();
private:
	bool isRunning = false;
	int cnt = 0;
	SDL_Window *window;
	SDL_Renderer *renderer;
	//Snake related 
	SDL_Rect snakeHead;
	int bodyLength = 1; //Starts at 1 due to the head
	//FPS
	Uint32 startTime;
};