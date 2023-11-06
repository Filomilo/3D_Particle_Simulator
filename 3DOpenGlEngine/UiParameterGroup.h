#pragma once
#include <ostream>

#include "UiParameter.h"
#include <vector>
class UiParameterGroup
{
private:
	std::string name;


	std::vector<std::shared_ptr<UiParameter>> parameters_;

	int selectedParamater = 0;


public:
	explicit UiParameterGroup(const std::string& name)
		: name(name)
	{
	}


	std::string get_name() const
	{
		return name;
	}

	void set_name(std::string name)
	{
		this->name = name;
	}

	void icreaseSelection()
	{
		selectedParamater = (selectedParamater + 1) % parameters_.size();
	}
	void decreaseSelection()
	{
		selectedParamater = (selectedParamater - 1) % parameters_.size();
	}

	void increaseSelectedParam()
	{
		parameters_[selectedParamater]->increaseVal();
	}

	void decreaseSelectedParam()
	{
		parameters_[selectedParamater]->decreaseVal();
	}

	void addParameter(std::shared_ptr<UiParameter> ui_parameter)
	{
		parameters_.push_back(ui_parameter);
	}
	friend std::ostream& operator<<(std::ostream& os, const UiParameterGroup& obj)
	{
		 os << "name: " << obj.name<<": \n";
		int i = 0;
		for (std::shared_ptr<UiParameter> element : obj.parameters_)
		{
			if (obj.selectedParamater == i)
				os << "Selected: ";
			os << *element << std::endl;
				i++;
		}
		os << std::endl;
		return  os;
	}

	std::vector<std::shared_ptr<UiParameter>> getParamters()
	{
		return parameters_;
	}

	int getSelected()
	{
		return selectedParamater;
	}
};

