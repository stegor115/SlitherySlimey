#include <iostream>
#include "SDL.h"

class Game {
public:
	//Constructor/Destructor
	Game();
	~Game();

	void init(const char* title, int width, int height);

	void handleEvents();
	void update();
	bool running() { return isRunning; };
	void render();
	void clean();
private:
	bool isRunning = false;
	int cnt = 0;
	SDL_Window *window;
	SDL_Renderer *renderer;
};