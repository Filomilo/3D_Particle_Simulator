#pragma once
#include "Force.h"

class Gravity:
public Force
{
private:
	const float G = 9.8;

public:
	void affect(Point* pt, float timeVal) override
	{
		Vector3f* V =(Vector3f*) pt->getAttribute("V");
		V->y -= G*timeVal;
	}
};

