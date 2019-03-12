#pragma once
#include <SDL.h>
#include <SDL_image.h>
class GameObject
{
public:
	GameObject();
	~GameObject();
	enum type { MISSILE1,MISSILE2,FISH1,FISH2 };
	type Type;
	void UpdatePosition();
	void Init(SDL_Renderer *R);
	bool LoadTexture(char *filename);
	bool Draw();
	int x, y;
	int v_x, v_y;
	int width, height;
	int screenwidth, screenheight;
	bool IsWithinScreenBounds(int x, int y);


	SDL_Renderer * renderer;
	SDL_Texture * texture;
};

