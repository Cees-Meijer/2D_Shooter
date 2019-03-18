#pragma once
#include <list>
#include "source.h"
#include "GameObject.h"
#include "player.h"

#define GRID_SPACING 32
class GameObjects
{
public:
	GameObjects();
	~GameObjects();
	std::list<GameObject*> objects_list;
	std::list<GameObject*> objects_delete_list;
	void AddMissile(Player *, int V_X, int V_Y);
	void AddFish(int x, int y,int V_X, int V_Y, SDL_Renderer *renderer);
	void Remove(GameObject* M);
	void UpdateAndDraw();
	GameObject* GOArray[SCREEN_WIDTH ][SCREEN_HEIGHT];


};

