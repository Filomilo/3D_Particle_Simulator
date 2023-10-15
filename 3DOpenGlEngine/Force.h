#pragma once
#include "Point.h"

class Force
{
private:

public:
	virtual void affect(Point* pt, float timeVal) = 0;


};

