/**
 * @file Simulatable.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file containg class of updatable
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "Updatable.h"
/**
 * @brief class of Sumualtable used in simulation
 * 
 * calss that add rest to udpatable virutal class
 * 
 */
class Simulatable :
	public Updatable
{
public:
	Simulatable();
	~Simulatable();

/**
 * @brief virtual method allwing to restt siumlation defined by this class instance
 * 
 */
	virtual void reset() = 0;

};

