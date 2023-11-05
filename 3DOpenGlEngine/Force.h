#pragma once
#include "Point.h"
#include "Parametrized.h"
class Force: public Parametrized
{
private:

public:
	virtual void affect(Point* pt, float timeVal) = 0;
	virtual UiParameterGroup* getParameterGroup() = 0;

};

