#include "Wave.h"



Wave::Wave()
{
}

Wave::~Wave()
{
}

void Wave::UpdateAndDraw() 
{
	x += 1; if (x == 0) { x = -1024; }
	Draw();
}