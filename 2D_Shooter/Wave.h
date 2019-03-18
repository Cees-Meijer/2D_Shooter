#pragma once
#include "GameObject.h"
class Wave :
	public GameObject
{
public:
	Wave();
	~Wave();
	void UpdateAndDraw();
};

