#pragma once
#include "Emitter.h"
class BoxEmitter :
    public Emitter
{
	Vector3f size;
private:

	Vector3f getNewPointPosition() override
	{
		Vector3f pos = Vector3f((float)rand() / RAND_MAX * size.x - size.x / 2,
			(float)rand() / RAND_MAX * size.y - size.y / 2,
			(float)rand() / RAND_MAX * size.z - size.z / 2
		);
		return pos;

	}
	Vector3f getNewColor() override
	{
		return  Vector3f(1, 1, 1);
	}
	Vector3f getNewVelocity() override
	{
		return  Vector3f(0, 0, 0);
	}

	float getNewSize() override
	{
		return  100;
	}

public:
	BoxEmitter(Vector3f pos, Vector3f size)
	{
		set_position(pos);
		this->size = size;
	}


};

