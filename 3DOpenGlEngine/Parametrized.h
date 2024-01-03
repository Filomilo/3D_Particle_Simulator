/**
 * @file Parametrized.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file coanating paremtairezed virtual template
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once
#include "UiParameterGroup.h"

class Parametrized
{
public:
	/**
	 * virtual method to defined objecfts that can get pareamter gorup for gui
	 * 
	 * \return 
	 */
	virtual std::shared_ptr<UiParameterGroup> getParameterGroup()=0;
};

