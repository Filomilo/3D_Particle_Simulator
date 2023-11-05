#pragma once
#include <ostream>

#include "Updatable.h"
#include "_3DEngine.h"
#include "UiParameterGroup.h"
#include "UiText.h"
#include <sstream>

class UiSystem : public Updatable, public UiText
{
private:


	std::vector<UiParameterGroup*> groups;

	int activegroup=0;

	void incrementGroup()
	{
		activegroup = (activegroup + 1) % groups.size();
		
	}

	void updateGroupText()
	{
		std::stringstream stream;
		stream << groups.at(activegroup)->get_name() << ": "<<"\n\n";
		int i=0;
		for(UiParameter* param : groups.at(activegroup)->getParamters())
		{
			if(groups.at(activegroup)->getSelected() == i)
			{
				stream <<"::::"<< param->getName() << ": " << param->getVal() << '\n';
			}
			else
			stream << param->getName() << ": " << param->getVal()<<'\n';
			i++;
		}
		this->setText(stream.str());
	}


public:
	UiSystem()
		: UiText("-", 0.008)
	{
	}

	void addParameterGroup( UiParameterGroup* ui_parameter_group)
	{
		groups.push_back(ui_parameter_group);
		updateGroupText();
	}

	void update(float timeElpased);

	friend std::ostream& operator<<(std::ostream& os,  UiSystem& obj)
	{
		return os << *obj.groups[obj.activegroup];
	}
};

