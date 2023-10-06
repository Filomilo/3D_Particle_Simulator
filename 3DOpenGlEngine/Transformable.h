#pragma once
#include <glm/fwd.hpp>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include "Vector3f.h"

class Transformable
{

private:

	Vector3f position;
	Vector3f rotation;
	Vector3f scale;


public:


	Transformable()
	{
		scale.x = 1;
		scale.y = 1;
		scale.z = 1;
	}

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

	void rotateY(float degrees)
	{
		this->rotation = this->rotation + Vector3f(0, degrees, 0);
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
	void set_scale(float scale)
	{
		this->scale = Vector3f(scale, scale, scale);
	}

	glm::mat4 getTransformationMatrix()
	{
		glm::mat4 mat = glm::mat4(1);
		mat = glm::translate(mat, glm::vec3(position.x, position.y, position.z));
		mat = glm::rotate(mat, glm::radians((float)this->get_rotation().x),glm::vec3(1,0,0));
		mat = glm::rotate(mat, glm::radians((float)this->get_rotation().y), glm::vec3(0, 1, 0));
		mat = glm::rotate(mat, glm::radians((float)this->get_rotation().z), glm::vec3(0, 0, 1));
		mat = glm::scale(mat, glm::vec3(scale.x, scale.y, scale.z));
		return mat;
	}





};

