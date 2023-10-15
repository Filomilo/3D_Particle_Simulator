#pragma once
#include "Emitter.h"
class BoxEmitter :
    public Emitter
{
	Vector3f size;
private:

	Vector3f getNewPointPosition() override
	{
		Vector3f positon = getFullPositon();
		Vector3f pos = Vector3f((float)rand() / RAND_MAX * size.x - size.x / 2+ positon.x,
			(float)rand() / RAND_MAX * size.y - size.y / 2 + positon.y,
			(float)rand() / RAND_MAX * size.z - size.z / 2 + positon.z
		);
		return pos;

	}
	Vector3f getNewColor() override
	{
		return  Vector3f(1, 1, 1);
	}
	Vector3f getNewVelocity() override
	{
		return  Vector3f(0, -1, 0);
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

