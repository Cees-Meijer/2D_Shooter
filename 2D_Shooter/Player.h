#pragma once
#include "GameObject.h"
#include <SDL.h>
#include <SDL_image.h>
class Player : public GameObject
{
public:
	Player();
	~Player();
	void HandleEvent(SDL_Event *event);
	void UpdatePosition();
	enum shot_state{IDLE,FIRE1,FIRE2,SHOT_HANDLED};
	shot_state shoot;
};

