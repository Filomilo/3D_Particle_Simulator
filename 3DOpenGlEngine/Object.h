#pragma once
#include <map>
#include <string>

#include "Attribute.h"
#include "Vector4f.h"

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
		std::map<std::string,Attribute*>::iterator it= this->attributes.find(name);
		Attribute* attrib;
		if(it== this->attributes.end())
		{
			attrib = new Vector4f(0,0,0,0);
			this->setAttribute(name, attrib);
		}
		else
		{
			attrib = it->second;
		}

		return attrib;
	}

	bool isThereAttrib(std::string name)
	{
		return this->attributes.find(name) != this->attributes.end();
	}


	~Object ()
	{
		for (std::pair<std::string, Attribute*> element: attributes)
		{
			delete element.second;
		}
	}
};

