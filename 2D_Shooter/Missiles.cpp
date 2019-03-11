#include "missiles.h"


Missiles::Missiles()
{
	missile_list.clear();
	missile_delete_list.clear();
}


Missiles::~Missiles()
{
}



void Missiles::Add(Player * player,int V_X, int V_Y) {
	//void Missiles::Add(int X, int Y,  SDL_Renderer *r) {
	Missile *M = new Missile();
	M->Init(player->renderer);
	
	char missile_filename[] = { "images\\pulse.png" };
	M->LoadTexture(missile_filename);
	int missile_offset = (player->width / 2) - M->width/2;
    M->x = player->x+ missile_offset; M->y = player->y; M->v_x = V_X; M->v_y = V_Y;
	missile_list.push_back(M);
}

void Missiles::Remove(Missile* M)
{
	missile_delete_list.push_back(M);
}

void Missiles::UpdateAndDraw()
{
	if (missile_list.size() == 0) { return; }
	for (auto const& missile : missile_list)
	{
		missile->UpdatePosition();
		if (missile->IsWithinScreenBounds(missile->x, missile->y))
		{
			missile->Draw();
		}
		else
		{
			missile_delete_list.push_back(missile);
		}
	}
	// Now remove all missiles from the list that are no longer visible, or manually marked for deletion.
	for (auto const& missile : missile_delete_list) { missile_list.remove(missile); }
}