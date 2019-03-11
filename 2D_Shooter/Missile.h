#pragma once
#include "GameObject.h"
class Missile :
	public GameObject
{
public:
	Missile();
	~Missile();
	void HandleEvent(SDL_Event *event);
	void UpdatePosition();
};

