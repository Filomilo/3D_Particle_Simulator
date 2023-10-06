#pragma once

#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include "Attribute.h"
#include "Vector3f.h"

class ShaderProgram
{

	unsigned int ID;
	std::map<std::string, Attribute::Types> AttributesRequiredMap;
	std::list<std::string> AttributesRequiredList;
	int vertexSize = 0;

	std::string getTextFile(std::string file)
	{
		std::stringstream stream;
		std::ifstream input;
		input.open(file);
		stream << input.rdbuf();
		return stream.str();
	}


public:
	

	ShaderProgram(std::string vertexShaderSource, std::string fragmentShaderSource)
	{

		int  success;
		char infoLog[512];
		

		std::string vertexCode = this->getTextFile(vertexShaderSource);
		const char* vertexCodeArray = vertexCode.c_str();
		unsigned int vertexShader;
		
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		
		glShaderSource(vertexShader, 1, &vertexCodeArray, NULL);
		glCompileShader(vertexShader);


		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			throw std::runtime_error(infoLog);
		}


		std::string fragmentCode = this->getTextFile(fragmentShaderSource);
		const char* fragmentCodeArray = fragmentCode.c_str();
		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentCodeArray, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			throw std::runtime_error(infoLog);
		}


		ID = glCreateProgram();
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);

		glGetShaderiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ID, 512, NULL, infoLog);
			throw std::runtime_error(infoLog);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);


		this->addAttribute("P",Attribute::VECTOR3F);

	}
	void use()
	{
		glUseProgram(ID);
	}

	void setBool(const std::string& name, bool val)
	{
		this->use();
		glUniform1i(glGetUniformLocation(ID, name.c_str()), val);

	}

	void setInt(const std::string& name, int val)
	{
		this->use();

		glUniform1i(glGetUniformLocation(ID, name.c_str()), val);
	}
	void setFloat(const std::string& name, float val)
	{
		this->use();

		glUniform1f(glGetUniformLocation(ID, name.c_str()), val);
	}



	void setArray(const std::string& name, int size, float* pointer)
	{
		this->use();

		glUniform1fv(glGetUniformLocation(ID, name.c_str()), size, pointer);
	}

	void unuse()
	{
		glUseProgram(0);
	}

	void setVector3f(const std::string& name, const Vector3f& vector3_f)
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), vector3_f.x, vector3_f.y, vector3_f.z);
	}



	void setMatrix4(const std::string& name, const glm::mat4& mat4)
	{
		this->use();
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat4));
	}


	void addAttribute(std::string atribName, Attribute::Types type)
	{
		this->AttributesRequiredList.push_back(atribName);
		this->AttributesRequiredMap.insert(std::pair<std::string, Attribute::Types>(atribName, type));
		this->vertexSize += type;
	}

	std::list<std::string>& getAttributeList()
	{
		return this->AttributesRequiredList;
	}

	std::map<std::string, Attribute::Types>& getAttributeMap()
	{
		return this->AttributesRequiredMap;
	}




	unsigned int getVertexSizeRequired()
	{
		return this->vertexSize;
	}

};
