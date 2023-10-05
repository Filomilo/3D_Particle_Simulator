#pragma once
#include <ostream>

class Attribute
{

public:
	enum Types
	{
		NONE=0,
		FLOAT,
		VECTOR2F,
		VECTOR3F,
		VECTOR4F,
	};


	virtual int getSize() const
	{
		return NONE;
	}


	friend std::ostream& operator<<(std::ostream& os, const Attribute& obj)
	{
		os << "NONE Attribute";
		return os;
	}

	~Attribute()
	{}
};

