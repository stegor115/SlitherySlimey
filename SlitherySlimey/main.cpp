#include <iostream>
#include "Game.h"
#undef main

Game *game = nullptr;
//Test
int main() {
	srand(time(NULL));
	int WINDOW_WIDTH = 600;
	int WINDOW_HEIGHT = 600;
	game = new Game();
	game->init("Slithery Slimey", WINDOW_WIDTH, WINDOW_HEIGHT);

	while (game->running()) {
		game->handleEvents();
		game->update();
	} //end while

	game->clean();
	return 0;
}


