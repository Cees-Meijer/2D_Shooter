#include "GameObject.h"
#include "gameobjects.h"
#include "Source.h"
#include <SDL.h>


    GameObject::GameObject() {
		screenheight = 0; screenwidth = 0;
		width = 0; height = 0;
		renderer = nullptr; texture = nullptr;
		v_x = 0; v_y = 0;
		x = 0; y = 0;
		Type = type::MISSILE1;
	}
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
	///<summary> Check if this game object collides with another gameobject by check for overlap on the bounding box.</summary>
	bool GameObject::Collision(GameObject* other_object)
	{
     if(x < other_object->x + other_object->width &&
        x + width > other_object->x &&
        y < other_object->y + other_object->height &&
        y + height > other_object->y)
        {
         printf("Collision !");
		 return true;
        }
	 return false;
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

#ifdef SHOW_BOUNDING_BOX
		SDL_Rect bounding_box;
		bounding_box.x =( (x+width/2) /GRID_SPACING) * GRID_SPACING ; bounding_box.y = ((y+height/2)/GRID_SPACING)*GRID_SPACING ;
		bounding_box.w = GRID_SPACING; bounding_box.h = GRID_SPACING;
		SDL_RenderDrawRect(renderer,&bounding_box);
#endif
		return true;
	}
	///<summary>Check if the object is within the bounds of the renderer screen. Boundaries were set in the 'Init' function.</summary>
	bool GameObject::IsWithinScreenBounds(int x, int y) {
		if (x < screenwidth && x>0 && y > 0 && y < screenheight) { return true; }
		else { return false; }
	}

	
