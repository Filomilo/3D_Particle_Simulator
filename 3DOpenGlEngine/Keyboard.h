#pragma once

#include <ostream>

#include "Key.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class Keyboard
{

	

public:
	Key Tab;
	Key arrowDown;
	Key arrowUp;
	Key arrowRight;
	Key arrowLeft;
	Key space;
	Key Delete;

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

