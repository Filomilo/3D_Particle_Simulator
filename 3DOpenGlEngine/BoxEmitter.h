/**
 * @file BoxEmitter.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file coantiang box emiitrer
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include "Emitter.h"
/**
 * @brief emitter inheterd clas for box emitter 
 * 
 */
class BoxEmitter :
    public Emitter
{
	/**
	 * @brief szie of emtter
	 * 
	 */
	Vector3f size;
private:
/**
 * @brief Get the New Point Position object
 * 
 * @return Vector3f 
 */
	Vector3f getNewPointPosition() override
	{
		Vector3f positon = getFullPositon();
		Vector3f pos = Vector3f((float)rand() / RAND_MAX * size.x - size.x / 2+ positon.x,
			(float)rand() / RAND_MAX * size.y - size.y / 2 + positon.y,
			(float)rand() / RAND_MAX * size.z - size.z / 2 + positon.z
		);
		return pos;

	}

	/**
	 * @brief Get the New Color object
	 * 
	 * @return Vector3f 
	 */
	Vector3f getNewColor() override
	{
		return  Vector3f(1,1,1);
	}
	/**
	 * @brief Get the New Velocity object
	 * 
	 * @return Vector3f 
	 */
	Vector3f getNewVelocity() override
	{
		return  Vector3f(0, 0, 0);
	}
/**
 * @brief Get the New Size object
 * 
 * @return float 
 */
	float getNewSize() override
	{
		return  100;
	}

public:
/**
 * @brief Construct a new Box Emitter object
 * 
 * @param pos 
 * @param size 
 */
	BoxEmitter(Vector3f pos, Vector3f size)
	{
		set_position(pos);
		this->size = size;
	}


};

