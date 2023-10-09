#pragma once
#include <iostream>

#include "Vector2f.h"

class Mouse
{
private:


		enum
		{
			LPM=0,
			RPM,
			MPM
		};

		enum
		{
			RELEASE=0,
			PUSH
		};
		
		
		Vector2f position=0;
		Vector2f offset=0;
		float scrollMovement=0;
		bool isPressing[3];
		bool isClick[3];
		bool isReleasing[3];
		

public:

	Mouse()
	{
		std::fill(isPressing, isPressing + 3, false);

		reset();
	};
	~Mouse() {}
	

	void setMousePostition(int screenWidth,int screenHeight, int x, int y)
	{
		this->offset.x = position.x - x / (float)screenWidth;
		this->offset.y = position.y - y / (float)screenHeight;
		this->position.x = x / (float)screenWidth;
		this->position.y = y / (float)screenHeight;

		//std::cout << position.x << std::endl;
	}


	float getX()
	{
		return  this->position.x;
	}

	float getY()
	{
		return  this->position.y;
	}

	Vector2f getPos()
	{
		return position;
	}


	Vector2f getMouseOffset()
	{
		return this->offset;
	}

	void reset()
	{
	
		this->offset = Vector2f(0,0);
		this->scrollMovement = 0;

		
		std::fill(isClick, isClick + 3, false);
		std::fill(isReleasing, isReleasing + 3, false);

	}


	void updateMouseButton(int type,int param)
	{
		if(param==PUSH)
		{
			isPressing[type] = true;
			isClick[type] = true;
		}
		else
		{
			isPressing[type] = false;
			isReleasing[type] = true;
		}
	}

	void updateScroll(float scrollMove)
	{
		this->scrollMovement+= scrollMove;
	}


	int getScrollMovement()
	{
		return scrollMovement;
	}

	bool getIsRightClick()
	{
		return isClick[RPM];
	}

	bool getIsLeftClick()
	{
		return isClick[LPM];
	}

	bool getIsMiddleClick()
	{
		return isClick[MPM];
	}

	bool getIsRightRealsed()
	{
		return isReleasing[RPM];
	}

	bool getIsLefteReleased()
	{
		return isReleasing[LPM];
	}

	bool getIsMiddleReleased()
	{
		return isReleasing[MPM];
	}

	bool getIsRightPressed()
	{
		return isPressing[RPM];
	}

	bool getIsLeftePressed()
	{
		return isPressing[LPM];
	}

	bool getIsMiddlePressedd()
	{
		return isReleasing[MPM];
	}

};

