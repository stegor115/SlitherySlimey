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
	case SDL_KEYDOWN: //If key is pressed
		switch (event.key.keysym.sym) //Getting key presses
		{
		case SDLK_w:
			//Switch booleans to allow north.
			std::cout << "Direction: North" << std::endl;
			/*this->north = true;
			this->south = false;
			this->east = false;
			this->west = false;*/
			this->snakeHead.y -= 50;
			break;
		case SDLK_s:
			std::cout << "Direction: South" << std::endl;
			this->snakeHead.y += 50;
			break;
		case SDLK_a:
			std::cout << "Direction: West" << std::endl;
			this->snakeHead.x -= 50;
			break;
		case SDLK_d:
			std::cout << "Direction: East" << std::endl;
			this->snakeHead.x += 50;
			break;
		default:
			break;
		} //end inner switch statement
			break;
	case SDL_QUIT :
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update() {
	cnt++;
	//Direction handling
	/*if (this->north) {
		this->snakeHead.y -= 50;
	}
	else if (this->south) {
		this->snakeHead.y += 50;
	}
	else if (this->east) {
		this->snakeHead.x += 50;
	}
	else if (this->west) {
		this->snakeHead.x += -50;
	}*/
	//this->snakeHead.x = (FPS*time()/1000); //Saving for later
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