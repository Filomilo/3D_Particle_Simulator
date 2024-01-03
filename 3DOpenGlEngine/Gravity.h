/**
 * @file Gravity.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief fle coanitng gravity force calss
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include "Force.h"
#include "UiParameterGroup.h"
/**
 * @brief gravity forcei mpleitnf force template
 * 
 */
class Gravity:
public Force
{
private:
/**
 * @brief gravity paremtert g force 
 * 
 */
	std::shared_ptr<Float>  G = std::make_shared<Float>(9.8);

public:
/**
 * @brief main method aect aprticels with gravity force
 * 
 * @param pt 
 * @param timeVal 
 */
	void affect(std::shared_ptr<Point> pt, float timeVal) override
	{
		 std::shared_ptr<Vector3f> V = std::dynamic_pointer_cast<Vector3f>( pt->getAttribute("V"));
		std::shared_ptr<Float> mass = std::dynamic_pointer_cast<Float>(pt->getAttribute("mass"));
		V->y -= (((*mass)*(*G)) * timeVal)[0];
	}
/**
 * @brief Get the Parameter Group object
 * 
 * created paremt group for graviyt force to be used in gui
 * 
 * @return std::shared_ptr<UiParameterGroup> 
 */
	std::shared_ptr<UiParameterGroup> getParameterGroup() override
	{
		std::shared_ptr<UiParameterGroup> ui_parameter_group = std::make_shared<UiParameterGroup>("Gravity");
		ui_parameter_group->addParameter(std::make_shared<UiParameter>("G", G, 0.1));
		return ui_parameter_group;
	}
};

