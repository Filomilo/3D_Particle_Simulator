#pragma once
#include <glm/fwd.hpp>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include "Math.h"
#include "Vector3f.h"

class Transformable
{

protected:

	glm::mat4 objectTransformation=glm::mat4(1);
	glm::mat4 originPointTransformation = glm::mat4(1);
	Vector3f rotation;


public:


	Transformable()
	{
		
	}

	Vector3f get_position() const
	{
		glm::vec3 position = glm::vec3(originPointTransformation[3]);
		return Vector3f(position);
	}



	Vector3f get_rotation() const
	{
		return rotation;
	}

	Vector3f get_scale() const
	{
		return Vector3f(glm::vec3(originPointTransformation * glm::vec4(1, 1, 1,1)));
	}


	
	void rotateY(float degrees)
	{
		rotation.y += degrees;
		this->originPointTransformation = glm::rotate(originPointTransformation,  glm::radians(degrees), glm::vec3(0.0f, 1.0f, 0.0f) );
	}
	void rotateX(float degrees)
	{
		rotation.x += degrees;
		this->originPointTransformation = glm::rotate(originPointTransformation, glm::radians(degrees), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	void rotateZ(float degrees)
	{
		this->originPointTransformation = glm::rotate(originPointTransformation, glm::radians(degrees), glm::vec3(0.0f, 0.0f, 1.0f));
	}

	void rotate(float degrees,Vector3f vec)
	{
		rotation.z += degrees;
		this->originPointTransformation = glm::rotate(originPointTransformation, glm::radians(degrees), vec.glm());
	}

	void set_position(Vector3f position)
	{
		originPointTransformation[3][0] = position.x; 
		originPointTransformation[3][1] = position.y; 
		originPointTransformation[3][2] = position.z; 
	}

	void set_position_object(Vector3f position)
	{
		objectTransformation[3][0] = position.x;
		objectTransformation[3][1] = position.y;
		objectTransformation[3][2] = position.z;
	}

	void set_rotation(Vector3f rotation) 
	{
		//// TODO: implement
	}

	void set_scale(Vector3f scale) 
	{
		//// TODO: immplement
	}
	void set_scale(float scale)
	{
		//// TODO: immplement
	}

	glm::mat4 getTransformationMatrix()
	{
	
		return objectTransformation;
	}

	void move(Vector3f offset)
	{
		originPointTransformation = glm::translate(originPointTransformation, offset.glm());
	}
	void moveIndendent(Vector3f offset)
	{
		objectTransformation = glm::translate(objectTransformation, offset.glm());
	}

	Vector3f getFullPositon()
	{
		glm::vec3 position = glm::vec3((originPointTransformation*objectTransformation)[3]);
		return Vector3f(position);
	}






};

