
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdio.h>
#include <chrono>
#include "Player.h"
#include "GameObjects.h"
#include "Wave.h"
#include "Source.h"



int main(int argc, char* args[]) {
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	SDL_Renderer *renderer=NULL;
	SDL_Texture *texture=NULL;
	SDL_Event event;
	//The surface contained by the window
	SDL_Surface* gScreenSurface = NULL;
	
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER) < 0) {
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
	GameObjects *objects = new GameObjects();

	GameObject *background = new GameObject();
	background->Init(renderer);
	char bg_filename[] = { "images\\Seafloor.bmp" };
	background->LoadTexture(bg_filename);

	Wave *wave = new Wave();
	wave->Init(renderer);
	char wave_filename[] = { "images\\Wave3.png" };
	wave->LoadTexture(wave_filename);
	wave->x = -1024; wave->y = 55;

	Uint32 start_ticks = SDL_GetTicks();
	Uint32 frame_ticks = SDL_GetTicks();
	unsigned long frame_counter = 0;
	int fish_interval =( rand() % 100) + 100; // between 1 and 2 seconds
	int fish_height = 0; int fish_speed = -1;
	while (1) 
		{
    	Uint32 diff = SDL_GetTicks() - frame_ticks;
		if (diff < 9) {SDL_Delay(1);  continue; } // 100 Frames per second
		frame_ticks = SDL_GetTicks();
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT){break;}
		if (frame_counter % fish_interval == 0) 
		 {
			fish_speed = rand() % 5 * -1;
			int rnd = (rand() % 7);
			fish_height = rnd * GRID_SPACING + GRID_SPACING/2  + 100;
			objects->AddFish(SCREEN_WIDTH, fish_height, fish_speed, 0, renderer);
		    fish_interval = (rand() % 500) + 200;
			//printf("Fish: rnd=%d, y=%d, spd=%d\r\n",rnd, fish_height, fish_speed);
 		}
		player->HandleEvent(&event);
		if (player->shoot == player->FIRE1 ) { objects->AddMissile(player, 0, -8); player->shoot = player->SHOT_HANDLED; }
		player->UpdatePosition();
		//We have a screen filling background, so there is no need to clear the background
		SDL_RenderCopy(renderer, background->texture, NULL, NULL);
		wave->UpdateAndDraw();
		objects->UpdateAndDraw();
		player->Draw();
		SDL_RenderPresent(renderer);
		
		frame_counter++;
	    }
	    Uint32 end_ticks = SDL_GetTicks();
		Uint32 diff = end_ticks - start_ticks;
		double fps = (double)frame_counter / (double)diff * 1000;
		std::cout << frame_counter << " frames rendered in " << diff << " ms ("<< fps << " fps)" << std::endl;

	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(window);
	SDL_Quit();
	player->~Player();
	wave->~Wave();
	return 0;
}

struct Timer
{
	Uint64 previous_ticks{};
	float elapsed_seconds{};

	void tick()
	{
		const Uint64 current_ticks{ SDL_GetPerformanceCounter() };
		const Uint64 delta{ current_ticks - previous_ticks };
		previous_ticks = current_ticks;
		static const Uint64 TICKS_PER_SECOND{ SDL_GetPerformanceFrequency() };
		elapsed_seconds = delta / static_cast<float>(TICKS_PER_SECOND);
	}
};

