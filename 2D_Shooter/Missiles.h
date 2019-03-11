#pragma once
#include <list>
#include "missile.h"
#include "player.h"
class Missiles
{
public:
	Missiles();
	~Missiles();
	std::list<Missile*> missile_list;
	std::list<Missile*> missile_delete_list;
	//void Add(int X, int Y, int V_X, int V_Y, SDL_Renderer *r);
	void Add(Player *, int V_X, int V_Y);
	void Remove(Missile* M);
	void UpdateAndDraw();

};

