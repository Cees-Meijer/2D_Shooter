#include "gameobjects.h"



GameObjects::GameObjects()
{
	objects_list.clear();
	objects_delete_list.clear();
	
	filenameTable[0] = string("images\\kingfish_2_left.png");
	
	for (int X = 0; X < SCREEN_WIDTH ; X++)
	{
		for (int Y = 0; Y < SCREEN_HEIGHT; Y++)
		{
			GOArray[X][Y] = nullptr;
		}
	}
}


GameObjects::~GameObjects()
{
}

void GameObjects::AddFish( int x, int y,int V_X, int V_Y, SDL_Renderer *renderer) {
	GameObject *GO = new GameObject();
	GO->Type = GO->FISH1;
	GO->Init(renderer);
	char fish_filename[] = { "images\\kingfish_2_left.png" };
	GO->LoadTexture(fish_filename);
	GO->x = x; GO->y = y; GO->v_x = V_X; GO->v_y = V_Y;
	objects_list.push_back(GO);
}


void GameObjects::AddMissile(Player * player,int V_X, int V_Y) {
	GameObject *GO = new GameObject();
	GO->Type = GO->MISSILE1;
	GO->Init(player->renderer);
	char missile_filename[] = { "images\\pulse.png" };
	GO->LoadTexture(missile_filename);
	int missile_offset = (player->width / 2) - GO->width/2;
    GO->x = player->x+ missile_offset; GO->y = player->y; GO->v_x = V_X; GO->v_y = V_Y;
	objects_list.push_back(GO);
}

void GameObjects::Remove(GameObject* M)
{
	objects_delete_list.push_back(M);
}

void GameObjects::UpdateAndDraw()
{
	if (objects_list.size() == 0) { return; }
	for (auto const& object : objects_list)
	{
		int X = (object->x + object->height / 2) / GRID_SPACING; int Y = (object->y + object->height/2) / GRID_SPACING;
		//int Y_Right = (object->y + object->width) / GRID_SPACING;

		GOArray[X][Y] = nullptr;
		object->UpdatePosition();
		 X = (object->x + object->height / 2) / GRID_SPACING;  Y = (object->y + object->height / 2) / GRID_SPACING;

		//if (object->Type == object->MISSILE1) { printf("%d,%d\r\n", X, Y); }
		if (GOArray[X][Y] != nullptr && GOArray[X][Y] != object)
		{
			printf("Collision!");
			if (object->Type != GOArray[X][Y]->Type) // Only when two different objects collide
			{
				objects_delete_list.push_back(object);
				objects_delete_list.push_back(GOArray[X][Y]);
				GOArray[X][Y] = nullptr;
			}
		}
		else { GOArray[X][Y] = object; }

		if (object->IsWithinScreenBounds(object->x, object->y))
		{
			object->Draw();
		}
		else
		{
			objects_delete_list.push_back(object);
		}
	}
	// Now remove all missiles from the list that are no longer visible, or manually marked for deletion.
	for (auto const& object : objects_delete_list) { objects_list.remove(object); }
}