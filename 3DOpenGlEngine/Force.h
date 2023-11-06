#pragma once
#include "Point.h"
#include "Parametrized.h"
class Force: public Parametrized
{
private:

public:
	virtual void affect(std::shared_ptr<Point> pt, float timeVal) = 0;
	virtual std::shared_ptr<UiParameterGroup> getParameterGroup() = 0;

};

