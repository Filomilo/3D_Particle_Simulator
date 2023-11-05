#pragma once
#include "Force.h"
#include "UiParameterGroup.h"

class Gravity:
public Force
{
private:
	 float G = 9.8;

public:
	void affect(Point* pt, float timeVal) override
	{
		Vector3f* V =(Vector3f*) pt->getAttribute("V");
		Float* mass = (Float*)pt->getAttribute("mass");
		V->y -= (((*mass)*G) * timeVal)[0];
	}

	UiParameterGroup* getParameterGroup() override
	{
		UiParameterGroup* ui_parameter_group = new UiParameterGroup("Gravity");
		ui_parameter_group->addParameter(new UiParameter("G", &this->G, 0.1));
		return ui_parameter_group;
	}
};

