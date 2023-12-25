/**
 * @file Vortex.h
 * @author fborowiec@wp.pl
 * @brief File containg class with Vortex Force
 * @version 0.1
 * @date 2023-12-25
 * 
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#pragma once
#include "Force.h"
/**
 * @brief Implementaion of vortex force for paricle simulation
 * 
 * Vortex force that extendeds class Froce, it implements virtual method affect,
 * to apply to glObject vortex force based on its attributes, It works by calculating new
 * velocaity vector based on it's postion form the center and adds it to current
 * object velocity multiply scale parameter, It also apply magnet froce that apply force 
 * in direction to closest point in a cricle of radius defined by radius paramter in order to keep 
 * object in the center
 */
class Vortex :
	public Force
{
private:
/**
 * @brief scale factor paremeter used in ui
 * 
 * paramter is used to scale new cortex force vector in simulation
 */
	std::shared_ptr<Float>  scale = std::make_shared<Float>(1);
	std::shared_ptr<Float>  radius = std::make_shared<Float>(1);
	std::shared_ptr<Float>  magnet = std::make_shared<Float>(0);



public:
/**
 * @brief applies vector force to current point
 * 
 * @param pt shared pointer to point affect during current simulation run
 * @param timeVal time offset from previous simulation run to scale force accrodingly
 */
	void affect(std::shared_ptr<Point> pt, float timeVal) override
	{
		std::shared_ptr<Vector3f> V = std::dynamic_pointer_cast<Vector3f>(pt->getAttribute("V"));
		std::shared_ptr<Float> mass = std::dynamic_pointer_cast<Float>(pt->getAttribute("mass"));
		std::shared_ptr<Vector3f> P = std::dynamic_pointer_cast<Vector3f>(pt->getAttribute("P"));

		float r = sqrt(pow(P->x, 2) + pow(P->z, 2));
		float alpha = atan(P->z / P->x);
		float fromRadiusDistannce =  (radius->x-r)/10;

	
		Vector3f newVel;
		newVel.x=P->x*fromRadiusDistannce*magnet->x;
	    newVel.z = P->z*fromRadiusDistannce*magnet->x;

		newVel.x += -P->z*scale->x;
		newVel.z += P->x*scale->x;


		V->x += newVel.x*timeVal;
		V->z += newVel.z*timeVal;
		V->y += newVel.y*timeVal;

	}

	std::shared_ptr<UiParameterGroup> getParameterGroup() override
	{
		std::shared_ptr<UiParameterGroup> ui_parameter_group = std::make_shared<UiParameterGroup>("Vortex");
		ui_parameter_group->addParameter(std::make_shared<UiParameter>("scale", scale, 0.1));
		ui_parameter_group->addParameter(std::make_shared<UiParameter>("magnet", magnet, 10));
		ui_parameter_group->addParameter(std::make_shared<UiParameter>("radius", radius, 0.1));
		return ui_parameter_group;
	}

};

