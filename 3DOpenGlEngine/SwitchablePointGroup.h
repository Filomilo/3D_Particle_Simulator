#pragma once


#include "PointGroup.h"
#include "PointGroupInstanced.h"
class SwitchablePointGroup:
public  PointGroup,
public PointGroupInstanced
{
private:
	bool isInstanced=false;

	void setMat(std::shared_ptr<Material> mat)
	{
		PointGroup::setMat(mat);
	}
	

	void addPoint(float x, float y, float z, float r, float g, float b, float pscale = 10)
	{
		PointGroup::addPoint(x, y, z, r, g, b, pscale);
	}

	void init()
	{
		if (isInstanced)
			PointGroupInstanced::init();
		else
			PointGroup::init();
	}
	
};

