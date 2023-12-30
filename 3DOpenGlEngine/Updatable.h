/**
 * @file Updatable.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file conaitng base virtual class for updatable obejct
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once
/**
 * @brief virtual class updatable
 * 
 * its a virtual class with one method used in 3d engine to updates obejct saved in the engine
 * 
 */
class Updatable
{


public:
/**
 * @brief main virtual method update
 * 
 * method that is defined to be used by obejct to update ti accordingle inside game loop
 * 
 * @param timeElpased time since preovis game update run to update object acordignly to time passed
 */
	virtual void update(float timeElpased) = 0;
};

