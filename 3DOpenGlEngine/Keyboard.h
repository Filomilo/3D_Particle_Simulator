/**
 * @file Keyboard.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file coinaitn class for handlign keyboard input
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <ostream>

#include "Key.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
/**
 * @brief class fo hanlding keyborad input input
 * 
 */
class Keyboard
{

	

public:
/**
 * @brief tab key
 * 
 */
	Key Tab;
	/**
	 * @brief arror down key
	 * 
	 */
	Key arrowDown;
	/**
	 * @brief arrowd down key
	 * 
	 */
	Key arrowUp;
	/**
	 * @brief arrow right key
	 * 
	 */
	Key arrowRight;
	/**
	 * @brief arrow left key
	 * 
	 */
	Key arrowLeft;
	/**
	 * @brief space key
	 * 
	 */
	Key space;
	/**
	 * @brief delete key
	 * 
	 */
	Key Delete;
/**
 * @brief update fucntion that update key states
 * 
 * @param key key to update
 * @param state state of key
 */
	void update(int key, int state)
	{
		switch (key)
		{
		case GLFW_KEY_TAB: Tab.update(state); break;
		case GLFW_KEY_LEFT: arrowLeft.update(state); break;
		case GLFW_KEY_RIGHT: arrowRight.update(state); break;
		case GLFW_KEY_UP: arrowUp.update(state); break;
		case GLFW_KEY_DOWN: arrowDown.update(state); break;
		case GLFW_KEY_SPACE: space.update(state); break;
		case GLFW_KEY_DELETE: Delete.update(state); break;
		}
	}
/**
 * @brief retets one itme vent thta houdl alreadt be handled
 * 
 */
	void reset()
	{
		Tab.reset();
		 arrowDown.reset();
		 arrowUp.reset();
		 arrowRight.reset();
		 arrowLeft.reset();
		 space.reset();
		 Delete.reset();
	}
/**
 * @brief helping funciton to print all of key board state
 * 
 * @param os 
 * @param obj 
 * @return std::ostream& 
 */
	friend std::ostream& operator<<(std::ostream& os, const Keyboard& obj)
	{
		return os
			<< "Tab: " << obj.Tab<<std::endl
			<< " arrowDown: " << obj.arrowDown << std::endl
			<< " arrowUp: " << obj.arrowUp << std::endl
			<< " arrowRight: " << obj.arrowRight << std::endl
			<< " arrowLeft: " << obj.arrowLeft << std::endl << std::endl;
	}
};

