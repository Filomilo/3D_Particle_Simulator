/**
 * @file Force.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file conaitng Force class
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include "Point.h"
#include "Parametrized.h"
/**
 * @brief Force class tempalte to be applied in simulation
 * 
 */
class Force: public Parametrized
{
private:

public:
/**
 * @brief main funtion to be appleid to point
 * 
 * @param pt 
 * @param timeVal 
 */
	virtual void affect(std::shared_ptr<Point> pt, float timeVal) = 0;
	/**
	 * @brief Get the Parameter Group object
	 * 
	 * created pareaemter group to be used in gui
	 * 
	 * @return std::shared_ptr<UiParameterGroup> 
	 */
	virtual std::shared_ptr<UiParameterGroup> getParameterGroup() = 0;

};

