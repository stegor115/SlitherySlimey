#include <iostream>
#include "Game.h"
#undef main

Game *game = nullptr;
//Test
int main() {
	int WINDOW_WIDTH = 800;
	int WINDOW_HEIGHT = 800;
	game = new Game();
	game->init("Slithery Slimey", WINDOW_WIDTH, WINDOW_HEIGHT);

	while (game->running()) {
		game->handleEvents();
		game->update();
		//game->render();
	} //end while

	game->clean();
	return 0;
}


