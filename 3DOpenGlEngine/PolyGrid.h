#pragma once
#include "Polygonal.h"
class PolyGrid :
    public Polygonal
{
public:
	PolyGrid(float width, float height, unsigned int rows = 2, unsigned int colums = 2)
	{
		
		//TOOD: implement mulitple rows for polygrid;
		this->addPoint(-width / 2, 0, -height / 2);
		this->addPoint(-width / 2, 0, height / 2);
		this->addPoint(width / 2, 0, height / 2);
		this->addPoint(width / 2, 0, -height / 2);
		this->addVertecies({ 0,1,2,3 });
		this->addFace({ 0,1,2 });
		this->addFace({ 0,2,3 });

	}

};