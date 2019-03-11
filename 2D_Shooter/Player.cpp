#include "GameObject.h"
#include "Player.h"

#include <SDL.h>

	Player::Player() : GameObject()	{}
	Player::~Player() {}

	void  Player::HandleEvent(SDL_Event *event)
	{
		SDL_KeyboardEvent *ke = nullptr;
		switch (event->type)
		{
		case SDL_KEYDOWN:
			ke = &event->key;
			if (ke->repeat == 0)
			{
				if (ke->keysym.scancode == SDL_SCANCODE_LEFT)
				{
					v_x = -10;
				}

				if (ke->keysym.scancode == SDL_SCANCODE_RIGHT)
				{
					v_x = 10;
				}

				if (ke->keysym.scancode == SDL_SCANCODE_SPACE && shoot == IDLE )
				{
					shoot = FIRE1; // Set shoot state untill it is handled by the player
				}
			}
			break;
		case SDL_KEYUP:
			ke = &event->key;
			if (ke->repeat == 0)
			{
				if (ke->keysym.scancode == SDL_SCANCODE_LEFT)
				{
					v_x = 0;
				}

				if (ke->keysym.scancode == SDL_SCANCODE_RIGHT)
				{
					v_x = 0;
				}
				if (ke->keysym.scancode == SDL_SCANCODE_SPACE && shoot == SHOT_HANDLED)
				{
					shoot = IDLE; // Ready for the next shot
				}
			}
		}
	}

	void Player::UpdatePosition() {
		x = x + v_x;
		if (x > screenwidth - width) { x = screenwidth - width; }
		if (x < 0) { x = 0; }
		y = y + v_y;
		
	}

	
