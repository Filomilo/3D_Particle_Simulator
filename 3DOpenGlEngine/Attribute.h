/**
 * @file Attribute.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file containg attirbute class
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include <ostream>
/**
 * @brief attrbiute class gor hangling value of diffent types
 * 
 */
class Attribute
{

public:
/**
 * @brief type of attributes handled
 * 
 */
	enum Types
	{
		NONE=0,
		FLOAT,
		VECTOR2F,
		VECTOR3F,
		VECTOR4F,
	};

/**
 * @brief size of vector 
 * 
 * @return int 
 */
	virtual int getSize() const
	{
		return NONE;
	}

/**
 * @brief helping functioni to print attribure vlaue
 * 
 * @param os 
 * @param obj 
 * @return std::ostream& 
 */
	friend std::ostream& operator<<(std::ostream& os, const Attribute& obj)
	{
		os << "NONE Attribute";
		return os;
	}

	~Attribute()
	{}
};

