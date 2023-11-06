#pragma once
#include <ostream>
#include <string>

#include "Float.h"

class UiParameter
{
	std::string name;
	std::shared_ptr<Float> parametertoChange;
	float paremeterChangeStep;

public:
	UiParameter(const std::string& name, std::shared_ptr<Float> parameterto_change, float paremeter_change_step)
		: name(name),
		  parametertoChange(parameterto_change),
		  paremeterChangeStep(paremeter_change_step)
	{
	}

	void increaseVal()
	{
		*parametertoChange = *parametertoChange+ paremeterChangeStep;
	}

	void decreaseVal()
	{
		*parametertoChange = *parametertoChange- paremeterChangeStep;
	}

	friend std::ostream& operator<<(std::ostream& os,  UiParameter& obj)
	{
		return os<< obj.name<<": "<<*obj.parametertoChange;
	}

	std::string getName()
	{
		return  name;
	}

	float getVal()
	{
		return parametertoChange->x;
	}


};

