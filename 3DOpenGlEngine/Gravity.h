#pragma once
#include "Force.h"
#include "UiParameterGroup.h"

class Gravity:
public Force
{
private:
	std::shared_ptr<Float>  G = std::make_shared<Float>(9.8);

public:
	void affect(std::shared_ptr<Point> pt, float timeVal) override
	{
		 std::shared_ptr<Vector3f> V = std::dynamic_pointer_cast<Vector3f>( pt->getAttribute("V"));
		std::shared_ptr<Float> mass = std::dynamic_pointer_cast<Float>(pt->getAttribute("mass"));
		V->y -= (((*mass)*(*G)) * timeVal)[0];
	}

	std::shared_ptr<UiParameterGroup> getParameterGroup() override
	{
		std::shared_ptr<UiParameterGroup> ui_parameter_group = std::make_shared<UiParameterGroup>("Gravity");
		ui_parameter_group->addParameter(std::make_shared<UiParameter>("G", G, 0.1));
		return ui_parameter_group;
	}
};

