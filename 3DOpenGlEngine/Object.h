#pragma once
#include <map>
#include <string>

#include "Attribute.h"
#include "Vector4f.h"

class Object
{
public:

	std::map<std::string, std::shared_ptr<Attribute>> attributes;

	void setAttribute(std::string name,  std::shared_ptr<Attribute> type)
	{
		this->attributes.insert_or_assign(name, type);
	}

	 std::shared_ptr<Attribute> getAttribute(std::string name)
	{
		std::map<std::string, std::shared_ptr<Attribute>>::iterator it= this->attributes.find(name);
		 std::shared_ptr<Attribute> attrib;
		if(it== this->attributes.end())
		{
			attrib =std::make_shared<Vector4f>(0,0,0,0);
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
		attributes.clear();
	}
};

