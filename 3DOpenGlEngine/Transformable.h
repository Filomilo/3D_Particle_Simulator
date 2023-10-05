#pragma once
#include "Vector3f.h"

class Transformable
{

private:

	Vector3f position;
	Vector3f rotation;
	Vector3f scale;


public:
	Vector3f get_position() const
	{
		return position;
	}

	Vector3f get_rotation() const
	{
		return rotation;
	}

	Vector3f get_scale() const
	{
		return scale;
	}


	void set_position(Vector3f position)
	{
		this->position = position;
	}

	void set_rotation(Vector3f rotation) 
	{
		this->rotation = rotation;
	}

	void set_scale(Vector3f scale) 
	{
		this->scale = scale;
	}

};

