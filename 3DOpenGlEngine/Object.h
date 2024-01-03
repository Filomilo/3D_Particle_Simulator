/**
 * @file Object.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file conaitng main object class
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once
#include <map>
#include <string>

#include "Attribute.h"
#include "Vector4f.h"
/**
 * @brief class object
 * 
 * main objet class, it deifned main object that excpected that every object can coniatins some kind of attivutes
 * 
 */
class Object
{
public:
/**
 * @brief map for conating attributes
 * 
 */
	std::map<std::string, std::shared_ptr<Attribute>> attributes;
/**
 * @brief Set the Attribute object
 * 
 * set attribute of object
 * 
 * @param name get name of object
 * @param type attrbute value 
 */
	void setAttribute(std::string name,  std::shared_ptr<Attribute> type)
	{
		this->attributes.insert_or_assign(name, type);
	}
/**
 * @brief Get the Attribute object
 * 
 * retruns attribure of object with sepcifed name
 * 
 * @param name 
 * @return std::shared_ptr<Attribute> 
 */
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
/**
 * @brief check if there s attibute of specifed name
 * 
 * @param name name of attribute
 * @return true 
 * @return false 
 */
	bool isThereAttrib(std::string name)
	{
		return this->attributes.find(name) != this->attributes.end();
	}

/**
 * @brief Destroy the Object object
 * 
 * clear atrbiutes
 * 
 */
	~Object ()
	{
		attributes.clear();
	}
};

