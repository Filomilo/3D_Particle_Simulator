/**
 * @file Math.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file conaintg some math function
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once
#include "Vector2f.h"
/**
 * @brief static class math desgined to help wht some of calculaiton
 * 
 */
class Math
{
public:

/**
 * @brief converte cartezian coorasinates to polor corridantes
 * 
 * @param cartezianCoords 
 * @return Vector2f 
 */
	static Vector2f cartezianToPolar(Vector2f cartezianCoords)
	{
		Vector2f polar;
		polar.x = std::sqrt(cartezianCoords.x * cartezianCoords.x + cartezianCoords.y * cartezianCoords.y);
		polar.y = std::atan2(cartezianCoords.y, cartezianCoords.x);
		return polar;
	}
	/**
	 * @brief converts polor coorindates to cartezian
	 * 
	 * @param polar 
	 * @return Vector2f 
	 */
	static Vector2f polarToCartezian(Vector2f polar)
	{
		Vector2f cartesian;
		cartesian.x = polar.x * std::cos(polar.y);
		cartesian.y = polar.x * std::sin(polar.y);
		return polar;
	}


};

