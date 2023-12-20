#pragma once
#include "Force.h"
class Vortex :
	public Force
{
private:
	std::shared_ptr<Float>  scale = std::make_shared<Float>(1);
	std::shared_ptr<Float>  radius = std::make_shared<Float>(1);
	std::shared_ptr<Float>  magnet = std::make_shared<Float>(1);



public:
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
		ui_parameter_group->addParameter(std::make_shared<UiParameter>("magnet", magnet, 0.1));
		ui_parameter_group->addParameter(std::make_shared<UiParameter>("radius", radius, 0.1));
		return ui_parameter_group;
	}

};

