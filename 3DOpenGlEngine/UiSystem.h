#pragma once
#include <ostream>

#include "Updatable.h"
#include "_3DEngine.h"
#include "UiParameterGroup.h"

class UiSystem : public Updatable
{
private:


	std::vector<UiParameterGroup*> groups;

	int activegroup=0;

	void incrementGroup()
	{
		activegroup = (activegroup + 1) % groups.size();
	}

public:

	void addParameterGroup( UiParameterGroup* ui_parameter_group)
	{
		groups.push_back(ui_parameter_group);
	}

	void update(float timeElpased);

	friend std::ostream& operator<<(std::ostream& os,  UiSystem& obj)
	{
		return os << *obj.groups[obj.activegroup];
	}
};

