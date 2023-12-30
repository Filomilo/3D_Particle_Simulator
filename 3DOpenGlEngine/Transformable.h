
/**
 * @brief file conating virtual class transformable
 * 
 */
#pragma once
#include <glm/fwd.hpp>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include "Math.h"
#include "Vector3f.h"
/**
 * @brief virtual class allwoign for transformation
 * 
 * virtual class containg values and mothod allowing for matrtx glm transformation in object
 * that inhertes from this class 
 * 
 * curently class probably contains error so it must be used iwth caution
 * 
 */
class Transformable
{

protected:
/**
 * @brief main obejct transformation matrix
 * 
 */
	glm::mat4 objectTransformation=glm::mat4(1);
	/**
	 * @brief matric allwoing for origin point transformation
	 * 
	 */
	glm::mat4 originPointTransformation = glm::mat4(1);
	/**
	 * @brief hel class coanting rotaitn
	 * 
	 * hel class saving prevois rotating transfomration to know how rotaee object is 
	 * 
	 */
	Vector3f rotation=Vector3f(0,0,0);

public:

/**
 * @brief Construct a new Transformable object
 * basic empty constructor
 * 
 */
	Transformable()
	{
		
	}
/**
 * @brief Get the position object
 * 
 * @return Vector3f postion of origin point
 */
	Vector3f get_position() const
	{
		glm::vec3 position = glm::vec3(originPointTransformation[3]);
		return Vector3f(position);
	}


/**
 * @brief Get the rotation object
 * 
 * @return Vector3f retruns rotation of object
 */
	Vector3f get_rotation() const
	{
		return rotation;
	}
/**
 * @brief Get the scale object
 * 
 * @return Vector3f scale of object
 */
	Vector3f get_scale() const
	{
		return Vector3f(glm::vec3(originPointTransformation * glm::vec4(1, 1, 1,1)));
	}


	/**
	 * @brief rotates object arounf y axis
	 * 
	 * @param degrees degress to rotate
	 */
	void rotateY(float degrees)
	{
		rotation.y += degrees;
		this->originPointTransformation = glm::rotate(originPointTransformation,  glm::radians(degrees), glm::vec3(0.0f, 1.0f, 0.0f) );
	}
	/**
	 * @brief rotates object around x axis
	 * 
	 * @param degrees degress to rotate
	 */
	void rotateX(float degrees)
	{
		rotation.x += degrees;
		this->originPointTransformation = glm::rotate(originPointTransformation, glm::radians(degrees), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	/**
	 * @brief rotate object around z axis
	 * 
	 * @param degrees degrees to roatate
	 */
	void rotateZ(float degrees)
	{
		this->originPointTransformation = glm::rotate(originPointTransformation, glm::radians(degrees), glm::vec3(0.0f, 0.0f, 1.0f));
	}
/**
 * @brief rotate object in degrese arounf specifed vector
 * 
 * @param degrees degrees to rotate
 * @param vec around vector vector
 */
	void rotate(float degrees,Vector3f vec)
	{
		rotation.z += degrees;
		this->originPointTransformation = glm::rotate(originPointTransformation, glm::radians(degrees), vec.glm());
	}
/**
 * @brief Set the origin point position
 * 
 * @param position postion of origin point to set
 */
	virtual void set_position(Vector3f position)
	{
		originPointTransformation[3][0] = position.x; 
		originPointTransformation[3][1] = position.y; 
		originPointTransformation[3][2] = position.z; 
	}
/**
 * @brief Set the position object object
 * 
 * @param position new postioni of obejct(not origin point)
 */
	void set_position_object(Vector3f position)
	{
		objectTransformation[3][0] = position.x;
		objectTransformation[3][1] = position.y;
		objectTransformation[3][2] = position.z;
	}
/**
 * @brief Set the rotation object
 * 
 * currecntly not implemented
 * 
 * @param rotation 
 */
	void set_rotation(Vector3f rotation) 
	{
		//// TODO: implement
	}

/**
 * @brief sclae origin point matrix acording to privided data 
 * 
 * @param scale vector to scale
 */
	void scale(const Vector3f& scale)
	{
		originPointTransformation = glm::scale(originPointTransformation, glm::vec3(scale.x, scale.y, scale.y));
	}
/**
 * @brief Get the Transformation Matrix object
 * 
 * multiplyies orign nad obejct matrix get full object transformation matrix
 * 
 * @return glm::mat4 full transformation matrix
 */
	glm::mat4 getTransformationMatrix()
	{
	
		return objectTransformation*originPointTransformation;
	}
/**
 * @brief moves object orign point by provided vector
 * 
 * @param offset vector to move object
 */
	virtual void move(Vector3f offset)
	{
		originPointTransformation = glm::translate(originPointTransformation, offset.glm());
	}
	/**
	 * @brief moves object matrix by priovided vector (not origin point)
	 * 
	 * @param offset vector move by
	 */
	void moveIndendent(Vector3f offset)
	{
		objectTransformation = glm::translate(objectTransformation, offset.glm());
	}
/**
 * @brief Get the Full Positon object
 * 
 * returns full object postion from cobming origin and object matrix
 * 
 * @return Vector3f 
 */
	Vector3f getFullPositon()
	{
		glm::vec3 position = glm::vec3((originPointTransformation*objectTransformation)[3]);
		return Vector3f(position);
	}
	/**
	 * @brief move object in y axis
	 * 
	 * @param yOffset value by what to move in y axis
	 */
	void moveY(double yOffset)
	{
		move(Vector3f(0, yOffset, 0));
	}





};

