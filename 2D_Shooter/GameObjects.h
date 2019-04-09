#pragma once
#include <list>
#include <vector>
#include <string>
#include <map>
#include "source.h"
#include "GameObject.h"
#include "player.h"
using namespace std;

#define GRID_SPACING 64
class GameObjects
{
public:
	GameObjects();
	~GameObjects();
	list<GameObject*> objects_list;
	list<GameObject*> objects_delete_list;
	// this is a map, where the keys are integers and the values are strings
	map<int, string> filenameTable;
	//list<int,string> image_filenames;
	void AddMissile(Player *, int V_X, int V_Y);
	void AddFish(int x, int y,int V_X, int V_Y, SDL_Renderer *renderer);
	void Remove(GameObject* M);
	void UpdateAndDraw();
	GameObject* GOArray[SCREEN_WIDTH][SCREEN_HEIGHT] = { 0 };


};

