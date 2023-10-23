#pragma once
#include <ostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class Key
{

	bool isClicked=false;
	bool isPressing=false;
	bool isReleased=false;

public:
	Key(){}


	void reset()
	{
		isClicked = false;
		isReleased = false;
	}

	void update(int state)
	{
		switch (state)
		{
		case GLFW_PRESS: isClicked = true; isPressing = true; break;
		case GLFW_REPEAT: isClicked = true; break;

		case GLFW_RELEASE: isReleased = true; isPressing = false; break;
		}
	}


	bool is_is_clicked() const
	{
		return isClicked;
	}

	bool is_is_pressing() const
	{
		return isPressing;
	}

	bool is_is_released() const
	{
		return isReleased;
	}

	friend std::ostream& operator<<(std::ostream& os, const Key& obj)
	{
		return os
			<< "isClicked: " << obj.isClicked
			<< " isPressing: " << obj.isPressing
			<< " isReleased: " << obj.isReleased;
	}
};

