#pragma once
#include <iostream>

#include "Vector2f.h"
/**
 * class for handling mouse input input in 3d egnine.
 */
class Mouse
{
private:

	/**
	 * enum stroing mouse buttons.
	 */
		enum
		{
			LPM=0,
			RPM,
			MPM
		};
		/**
		 * enum storing mouse button state.
		 */
		enum
		{
			RELEASE=0,
			PUSH
		};
		
		/**
		 * postion of mouse.
		 */
		Vector2f position=Vector2f(0,0);
		/**
		 * current movemnt of mouse.
		 */
		Vector2f offset = Vector2f(0, 0);
		/**
		 * current scroll movemnt of mouse.
		 */
		float scrollMovement=0;
		/**
		 * bool array stroing values of mouse button stae is pressing.
		 */
		bool isPressing[3];
		/**
		 * bool array stroing values of mouse buttons state is click.
		 */
		bool isClick[3];
		/**
		 * bool array for stroign vlaues of mouse buttons sate is pressing.
		 */
		bool isReleasing[3];
		

public:
	/**
	 * main contructor for mouse classs handler.
	 * 
	 */
	Mouse()
	{
		std::fill(isPressing, isPressing + 3, false);

		reset();
	};
	~Mouse() {}
	
	/**
	 * updated method for updatirng mouse movemnt and postion.
	 * 
	 * \param screenWidth 
	 * \param screenHeight
	 * \param x mous psoion in x axis
	 * \param y mosue postion in y axis
	 */
	void setMousePostition(int screenWidth,int screenHeight, int x, int y)
	{
		this->offset.x = position.x - x / (float)screenWidth;
		this->offset.y = position.y - y / (float)screenHeight;
		this->position.x = x / (float)screenWidth;
		this->position.y = y / (float)screenHeight;

		//std::cout << position.x << std::endl;
	}

	/**
	 * getter fro mouse positoin in x axis.
	 * 
	 * \return mouse postion in x axis
	 */
	float getX()
	{
		return  this->position.x;
	}
	/**
	 * getter for mouse postion in y axis
	 * 
	 * \return mouse postion in y axis
	 */
	float getY()
	{
		return  this->position.y;
	}
	/**
	 * getter for mouse postion.
	 * 
	 * \return 
	 */
	Vector2f getPos()
	{
		return position;
	}

	/**
	 * getter for mouse offset .
	 * 
	 * \return mouse currecnt offser
	 */
	Vector2f getMouseOffset()
	{
		return this->offset;
	}
	/**
	 * method called at end of engine loop to reste one time event that shoudl already be handled if they were supposed to.
	 * 
	 */
	void reset()
	{
	
		this->offset = Vector2f(0,0);
		this->scrollMovement = 0;

		
		std::fill(isClick, isClick + 3, false);
		std::fill(isReleasing, isReleasing + 3, false);

	}

	/**
	 * .
	 * 
	 * \param type
	 * \param param
	 */
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
/**
 * @brief updates scorll omvemnt
 * 
 * @param scrollMove 
 */
	void updateScroll(float scrollMove)
	{
		this->scrollMovement+= scrollMove;
	}

/**
 * @brief Get the Scroll Movement object
 * 
 * returns scroll movemnt
 * @return int 
 */
	int getScrollMovement()
	{
		return scrollMovement;
	}
/**
 * @brief Get the Is Right Click object
 * 
 * @return true 
 * @return false 
 */
	bool getIsRightClick()
	{
		return isClick[RPM];
	}
/**
 * @brief Get the Is Left Click object
 * 
 * @return true 
 * @return false 
 */
	bool getIsLeftClick()
	{
		return isClick[LPM];
	}
/**
 * @brief Get the Is Middle Click object
 * 
 * @return true 
 * @return false 
 */
	bool getIsMiddleClick()
	{
		return isClick[MPM];
	}
/**
 * @brief Get the Is Right Realsed object
 * 
 * @return true 
 * @return false 
 */
	bool getIsRightRealsed()
	{
		return isReleasing[RPM];
	}
/**
 * @brief Get the Is Lefte Released object
 * 
 * @return true 
 * @return false 
 */
	bool getIsLefteReleased()
	{
		return isReleasing[LPM];
	}
/**
 * @brief Get the Is Middle Released object
 * 
 * @return true 
 * @return false 
 */
	bool getIsMiddleReleased()
	{
		return isReleasing[MPM];
	}
/**
 * @brief Get the Is Right Pressed object
 * 
 * @return true 
 * @return false 
 */
	bool getIsRightPressed()
	{
		return isPressing[RPM];
	}
/**
 * @brief Get the Is Lefte Pressed object
 * 
 * @return true 
 * @return false 
 */
	bool getIsLeftePressed()
	{
		return isPressing[LPM];
	}
/**
 * @brief Get the Is Middle Pressedd object
 * 
 * @return true 
 * @return false 
 */
	bool getIsMiddlePressedd()
	{
		return isReleasing[MPM];
	}

};

