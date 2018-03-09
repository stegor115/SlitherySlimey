#include "Game.h"
//Global variables
int FPS = 60;
int SNAKE_SIZE = 25;
int velocity = 25;
Game::Game() {
}

Game::~Game() {

}

void Game::init(const char* title, int width, int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, 0);
		this->windowWidth = width;
		this->windowHeight = height;
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
			//Set up of food
			spawnFood();
			this->food.w = SNAKE_SIZE;
			this->food.h = SNAKE_SIZE;
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
			case SDLK_UP:
				//Switch booleans to allow north.
				std::cout << "Direction: North" << std::endl;
				this->north = true;
				this->south = false;
				this->east = false;
				this->west = false;
				break;
			case SDLK_s:
			case SDLK_DOWN:
				std::cout << "Direction: South" << std::endl;
				this->north = false;
				this->south = true;
				this->east = false;
				this->west = false;
				break;
			case SDLK_a:
			case SDLK_LEFT:
				std::cout << "Direction: West" << std::endl;
				this->north = false;
				this->south = false;
				this->east = false;
				this->west = true;
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				std::cout << "Direction: East" << std::endl;
				this->north = false;
				this->south = false;
				this->east = true;
				this->west = false;
				break;
			default:
				break;
			} //end inner switch statement
			break;
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			//SDL_Delay(500);
			break;
		} //end switch
}

void Game::update() {
	//Direction handling
	if (timer() > 150) { //Handles how fast snake can move per frame
		//Get tail information before shift!
		for (int i = 0; i < this->tailLength; ++i) {
			this->snakeTail[i] = this->snakeTail[i + 1];
		}
		if (tailLength != 0) {
			this->snakeTail[tailLength - 1].x = this->snakeHead.x;
			this->snakeTail[tailLength - 1].y = this->snakeHead.y;
			this->snakeTail[tailLength - 1].w = this->snakeHead.w;
			this->snakeTail[tailLength - 1].h = this->snakeHead.h;
		}
		//Move head
		if (this->north && this->snakeHead.y - velocity >= 0) {
			this->snakeHead.y -= velocity;
		}
		else if (this->south && this->snakeHead.y + velocity <= this->windowHeight-SNAKE_SIZE) {
			this->snakeHead.y += velocity;
		}
		else if (this->east && this->snakeHead.x + velocity <= this->windowWidth-SNAKE_SIZE) {
			this->snakeHead.x += velocity;
		}
		else if (this->west && this->snakeHead.x - velocity >= 0) {
			this->snakeHead.x -= velocity;
		}
		else {
			std::cout << "Game Over" << std::endl;
		}
		//Debugging
		//std::cout << "headX = " << this->snakeHead.x << " headY = " << this->snakeHead.y << std::endl;
		//Check to see if food was eaten
		if (eat()) {
			spawnFood();
		} //end if
		//Clear Screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //Sets color to black
		SDL_RenderClear(renderer); //Clears screen
		//Renders food
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0); //Sets color to red
		SDL_RenderFillRect(renderer, &this->food); //Sets up rectangle to render
		SDL_RenderPresent(renderer); //Renders
		//Draw snake rectangle
		SDL_SetRenderDrawColor(renderer, 0, 100, 0, 0); //Sets color to green
		SDL_RenderFillRect(renderer, &this->snakeHead); //Sets up rectangle to render
		SDL_RenderPresent(renderer); //Renders
		//Draw snake tail
		for (int i = 0; i < tailLength; ++i) {
			//std::cout << "tailX = " << this->snakeTail[i].x << " tailY = " << this->snakeTail[i].y << std::endl;
			SDL_SetRenderDrawColor(renderer, 0, 100, 0, 0); //Sets color to green
			SDL_RenderFillRect(renderer, &this->snakeTail[i]); //Sets up rectangle to render
			SDL_RenderPresent(renderer); //Renders
		}
		this->startTime = SDL_GetTicks();
	}//end time if
}

bool Game::eat() {
	if (this->snakeHead.x == this->food.x && this->snakeHead.y == this->food.y) {
		this->tailLength++;
		return true;
	}
	else {
		return false;
	}
}

void Game::spawnFood() {
	std::cout << "Spawning food: ";
	int tempRand = -1;
	//Set X
	while (tempRand == -1 ||  tempRand >= this->windowWidth - SNAKE_SIZE || tempRand % SNAKE_SIZE != 0) { //0 does not need to be checked since rand() will return 0->width 
		tempRand = rand() % this->windowWidth;
	}
	std::cout << " New FoodPosX = " << tempRand;
	this->food.x = tempRand;

	//Set Y
	tempRand = -1;
	while (tempRand ==0 -1 || tempRand >= this->windowHeight - SNAKE_SIZE || tempRand % SNAKE_SIZE != 0){ //0 does not need to be checked for same reason as above 
		tempRand = rand() % this->windowHeight;
	}
	std::cout << " New FoodPosY = " << tempRand << std::endl;
	this->food.y = tempRand;
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

Uint32 Game::timer() {
	return SDL_GetTicks() - this->startTime;
}