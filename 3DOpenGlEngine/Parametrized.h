#pragma once
#include "UiParameterGroup.h"

class Parametrized
{
public:
	virtual std::shared_ptr<UiParameterGroup> getParameterGroup()=0;
};

