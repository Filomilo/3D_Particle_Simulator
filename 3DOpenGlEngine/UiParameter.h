#pragma once
#include <ostream>
#include <string>

class UiParameter
{
	std::string name;
	float* parametertoChange;
	float paremeterChangeStep;

public:
	UiParameter(const std::string& name, float* parameterto_change, float paremeter_change_step)
		: name(name),
		  parametertoChange(parameterto_change),
		  paremeterChangeStep(paremeter_change_step)
	{
	}

	void increaseVal()
	{
		*parametertoChange += paremeterChangeStep;
	}

	void decreaseVal()
	{
		*parametertoChange -= paremeterChangeStep;
	}

	friend std::ostream& operator<<(std::ostream& os,  UiParameter& obj)
	{
		return os<< obj.name<<": "<<*obj.parametertoChange;
	}
};

