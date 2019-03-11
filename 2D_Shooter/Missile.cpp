#include "Missile.h"

Missile::Missile()
{

}



void Missile::UpdatePosition()
{
	x = x + v_x; y = y + v_y;
}

Missile::~Missile()
{
}
