#pragma once
#include "Vector2f.h"

class Math
{
public:


	static Vector2f cartezianToPolar(Vector2f cartezianCoords)
	{
		Vector2f polar;
		polar.x = std::sqrt(cartezianCoords.x * cartezianCoords.x + cartezianCoords.y * cartezianCoords.y);
		polar.y = std::atan2(cartezianCoords.y, cartezianCoords.x);
		return polar;
	}
	static Vector2f polarToCartezian(Vector2f polar)
	{
		Vector2f cartesian;
		cartesian.x = polar.x * std::cos(polar.y);
		cartesian.y = polar.x * std::sin(polar.y);
		return polar;
	}


};

