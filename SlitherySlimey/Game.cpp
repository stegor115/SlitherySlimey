#include "Game.h"
#define SNAKE_SIZE 20;

int FPS = 60;
Game::Game() {
}

Game::~Game() {

}

void Game::init(const char* title, int width, int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			SDL_RenderPresent(renderer);
			//Set up of snake
			this->snakeHead.x = width / 2;
			this->snakeHead.y = height / 2;
			this->snakeHead.w = SNAKE_SIZE;
			this->snakeHead.h = SNAKE_SIZE;
			this->startTime = SDL_GetTicks();
		} //end if

		isRunning = true;
	} //end if
} //end Init

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) 
	{
	case SDL_QUIT :
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update() {
	cnt++;
	//Setting up snake
	//Clear screen
	this->snakeHead.x = (FPS*time()/1000);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //Sets color to black
	SDL_RenderClear(renderer); //Clears screen
	//Draw rectangle
	SDL_SetRenderDrawColor(renderer, 0, 100, 0, 0); //Sets color to green
	SDL_RenderFillRect(renderer, &this->snakeHead); //Sets up rectangle to render
	SDL_RenderPresent(renderer); //Renders
}

void Game::render() {
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

Uint32 Game::time() {
	return SDL_GetTicks() - this->startTime;
}