/**
 * @file Key.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file coanting key class
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include <ostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
/**
 * @brief class for ahdnling spcefi ckeyboard key
 * 
 */
class Key
{
/**
 * @brief stae of si cliked on 
 * 
 */
	bool isClicked=false;
	/**
	 * @brief state of if key is pressed
	 * 
	 */
	bool isPressing=false;
	/**
	 * @brief sate of key if is relased
	 * 
	 */
	bool isReleased=false;

public:
	Key(){}

/**
 * @brief reset key one time event
 * 
 */
	void reset()
	{
		isClicked = false;
		isReleased = false;
	}
/**
 * @brief update key state
 * 
 * @param state 
 */
	void update(int state)
	{
		switch (state)
		{
		case GLFW_PRESS: isClicked = true; isPressing = true; break;
		case GLFW_REPEAT: isClicked = true; break;

		case GLFW_RELEASE: isReleased = true; isPressing = false; break;
		}
	}

/**
 * @brief return is key clicked
 * 
 * @return true 
 * @return false 
 */
	bool is_is_clicked() const
	{
		return isClicked;
	}
/**
 * @brief return is ke [resef]
 * 
 * @return true 
 * @return false 
 */
	bool is_is_pressing() const
	{
		return isPressing;
	}
/**
 * @brief return is key realsd
 * 
 * @return true 
 * @return false 
 */
	bool is_is_released() const
	{
		return isReleased;
	}
/**
 * @brief helping funciotn to print keybaord state
 * 
 * @param os 
 * @param obj 
 * @return std::ostream& 
 */
	friend std::ostream& operator<<(std::ostream& os, const Key& obj)
	{
		return os
			<< "isClicked: " << obj.isClicked
			<< " isPressing: " << obj.isPressing
			<< " isReleased: " << obj.isReleased;
	}
};

