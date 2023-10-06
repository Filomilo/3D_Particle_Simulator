#pragma once
#include <map>
#include <string>

#include "Attribute.h"

class Object
{
public:

	std::map<std::string, Attribute*> attributes;

	void setAttribute(std::string name, Attribute* type)
	{
		this->attributes.insert_or_assign(name, type);
	}

	Attribute* getAttribute(std::string name)
	{
		return this->attributes.find(name)->second;
	}

	bool isThereAttrib(std::string name)
	{
		return false;
	}


	~Object ()
	{
		for (std::pair<std::string, Attribute*> element: attributes)
		{
			delete element.second;
		}
	}
};

