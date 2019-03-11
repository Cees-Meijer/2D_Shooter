#include "GameObject.h"
#include <SDL.h>


	GameObject::GameObject() {}
	GameObject::~GameObject(){}
	
	///<summary>Intialise the Game Object. Set position and velocity to 0. Set the Renderer and store the screensizes </summary>
	void GameObject::Init(SDL_Renderer * R)
	{
		x = 0;
		y = 0;
		v_x = 0; v_y = 0;
		width = 0; height = 0;
		renderer = R;
		SDL_GetRendererOutputSize(renderer, &screenwidth, &screenheight);
	}
	
	void GameObject::UpdatePosition()
	{
		x = x + v_x; y = y + v_y;
	}

	/// <summary>
	/// Loads the texture from a .png or .bmp file.
	/// </summary>
	/// <param name="filename">The filename.</param>
	bool GameObject::LoadTexture(char *filename)
	{
		texture = IMG_LoadTexture(renderer, filename);
		if (texture == NULL) { return false; }
		SDL_QueryTexture(texture, NULL, NULL, &width, &height);
		return true;
	}

	bool GameObject::Draw()
	{
		if (texture == NULL || renderer == NULL) { return false; }
		SDL_Rect dest;
		dest.x = x;
		dest.y = y;
		dest.w = width;
		dest.h = height;
		SDL_RenderCopy(renderer, texture, NULL, &dest);
		return true;
	}
	///<summary>Check if the object is within the bounds of the renderer screen. Boundaries were set in the 'Init' function.</summary>
	bool GameObject::IsWithinScreenBounds(int x, int y) {
		if (x < screenwidth && x>0 && y > 0 && y < screenheight) { return true; }
		else { return false; }
	}

	
