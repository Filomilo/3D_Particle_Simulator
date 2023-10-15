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
		this->addVertex(0, { 0.000000, 1.000000 ,0.000000 }, { 0.0, 0.000000  });
		this->addVertex(1, { 0.000000, 1.000000, 0.000000 }, { 1.0 ,0.0  });
		this->addVertex(2, { 0.000000, 1.000000 ,0.000000 }, { 1.0, 1.0,});
		this->addVertex(3, { 0.000000, 1.000000, 0.000000 }, { 0.0, 1.0});

		this->addFace({ 0,1,2 });
		this->addFace({ 0,2,3 });

	}

};