/**
 * @file UiParameter.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file conating UI paramter class
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <ostream>
#include <string>

#include "Float.h"
/**
 * @brief Ui apramter class conating name of pramters, value, and change step
 * 
 */
class UiParameter
{
	/**
	 * @brief name of paramter
	 * 
	 */
	std::string name;
	/**
	 * @brief pointer to Float value changed by its instance
	 * 
	 */
	std::shared_ptr<Float> parametertoChange;
	/**
	 * @brief ste of change in paramter value
	 * 
	 */
	float paremeterChangeStep;

public:
/**
 * @brief Construct a new Ui Parameter object
 * 
 * @param name name of paramter
 * @param parameterto_change pointer to float to chagne
 * @param paremeter_change_step step of change between updates
 */
	UiParameter(const std::string& name, std::shared_ptr<Float> parameterto_change, float paremeter_change_step)
		: name(name),
		  parametertoChange(parameterto_change),
		  paremeterChangeStep(paremeter_change_step)
	{
	}
/**
 * @brief increses value by paramter change
 * 
 */
	void increaseVal()
	{
		*parametertoChange = *parametertoChange+ paremeterChangeStep;
	}
/**
 * @brief decreses value by paramter change step
 * 
 */
	void decreaseVal()
	{
		*parametertoChange = *parametertoChange- paremeterChangeStep;
	}
/**
 * @brief print method for console debbuging
 * 
 * @param os 
 * @param obj 
 * @return std::ostream& 
 */
	friend std::ostream& operator<<(std::ostream& os,  UiParameter& obj)
	{
		return os<< obj.name<<": "<<*obj.parametertoChange;
	}
/**
 * @brief Get the Name object
 * 
 * @return std::string name of paramters
 */
	std::string getName()
	{
		return  name;
	}
/**
 * @brief Get the Val object
 * 
 * @return float retruns claue of parameter
 */
	float getVal()
	{
		return parametertoChange->x;
	}


};

