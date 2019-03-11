#include "Missile.h"

GameObject::GameObject()
{

}



void GameObject::UpdatePosition()
{
	x = x + v_x; y = y + v_y;
}

GameObject::~GameObject()
{
}
