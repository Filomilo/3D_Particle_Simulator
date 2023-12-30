/**
 * @file ShaderProgram.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file containg class Shader program
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <glad/glad.h>

#include <GL/gl.h>
#include <fstream>
#include <list>
#include <map>
#include <glm/fwd.hpp>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include "Camera.h"
#include "Math.h"
#include "Vector3f.h"
/**
 * @brief class  used to mange openg shader program
 * 
 */
class ShaderProgram
{
/**
 * @brief id of shader program used by opengl
 * 
 */
	unsigned int ID;
	/**
	 * @brief map of attrbutres used by shader program
	 * 
	 */
	std::map<std::string, Attribute::Types> AttributesRequiredMap;
	/**
	 * @brief order of attributes used by shader program
	 * 
	 */
	std::list<std::string> AttributesRequiredList;
	/**
	 * @brief size of vertex data in the sahder program
	 * 
	 */
	int vertexSize = 0;
	/**
	 * @brief Get the Text File object
	 * 
	 * retruns text of file used to create shader based on file input
	 * 
	 * @param file 
	 * @return std::string 
	 */
	std::string getTextFile(std::string file);


public:
	

	ShaderProgram(std::string vertexShaderSource, std::string fragmentShaderSource);
	void use();
	void setBool(const std::string& name, bool val);
	void setInt(const std::string& name, int val);
	void setFloat(const std::string& name, float val);
	void setArray(const std::string& name, int size, GLfloat* pointer);
	void unuse();
	void setVector3f(const std::string& name, const Vector3f& vector3_f);
	void setMatrix4(const std::string& name, const glm::mat4& mat4);
	void addAttribute(std::string atribName, Attribute::Types type);
	std::list<std::string>& getAttributeList();
	std::map<std::string, Attribute::Types>& getAttributeMap();
	unsigned int getVertexSizeRequired();
	void setCamera(std::string  name, Camera* camera);
	bool isLightAffeted();
	void applyLightData(Vector3f cameraPos);
};
