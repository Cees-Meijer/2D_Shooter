#include "Source.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdio.h>
#include <chrono>
#include "Player.h"
#include "Missile.h"
#include "Missiles.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

int main(int argc, char* args[]) {
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	SDL_Renderer *renderer=NULL;
	SDL_Texture *texture=NULL;
	SDL_Event event;
	SDL_Rect r;

	using Clock = std::chrono::steady_clock;
	using std::chrono::time_point;
	using std::chrono::duration_cast;
	using std::chrono::milliseconds;
	using namespace std::literals::chrono_literals;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Could not initialize SDL. SDL_Error: %s\n", SDL_GetError());
		return -1;
	}
	else {
		window = SDL_CreateWindow("Doppler Dash ))) )))", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Cannot create window. SDL_Error: %s\n", SDL_GetError());
			return -1;
		}
		gScreenSurface = SDL_GetWindowSurface(window);
	}
	printf("SDL Intialized. Starting Game\n");

	renderer = SDL_CreateRenderer(window, -1, 0);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	Player *player = new Player();
	player->Init(renderer);
	char player_filename[] = { "images\\AWAC.png" };	
	player->LoadTexture(player_filename);
	player->x = SCREEN_WIDTH/2; player->y = SCREEN_HEIGHT- player->height;
	Missiles *missiles = new Missiles();

	GameObject *background = new GameObject();
	background->Init(renderer);
	char bg_filename[] = { "images\\Seafloor.bmp" };
	background->LoadTexture(bg_filename);

	time_point<Clock> start = Clock::now();
	unsigned long frame_counter = 0;
	while (1) 
		{
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
		{
			break;
		}
		player->HandleEvent(&event);
		if (player->shoot == player->FIRE1 ) { missiles->Add(player, 0, -8); player->shoot = player->SHOT_HANDLED; }
		player->UpdatePosition();
		//SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		//SDL_RenderClear(renderer);	
		//We have a screen filling background, so there is no need to clear the background
		SDL_RenderCopy(renderer, background->texture, NULL, NULL);
		missiles->UpdateAndDraw();		
		player->Draw();
		SDL_RenderPresent(renderer);
		SDL_Delay(9); // About 100 frames per second
		frame_counter++;
	    }

		time_point<Clock> end = Clock::now();
		milliseconds diff = duration_cast<milliseconds>(end - start);
		double fps = (double)frame_counter / (double)diff.count() * 1000;
		std::cout << frame_counter << " frames rendered in " << diff.count() << " ms ("<< fps << " fps)" << std::endl;

	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(window);
	SDL_Quit();
	player->~Player();
	return 0;
}
