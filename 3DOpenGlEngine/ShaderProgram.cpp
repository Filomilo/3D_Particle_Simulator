#include "ShaderProgram.h"
#include <glad/glad.h>

#include <GL/gl.h>
#include <fstream>
#include <list>
#include <map>
#include <set>
#include <glm/fwd.hpp>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include "Camera.h"
#include "Light.h"
#include "Math.h"
#include "Vector3f.h"


ShaderProgram::ShaderProgram(std::string vertexShaderSource, std::string fragmentShaderSource)
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


	this->addAttribute("P", Attribute::VECTOR3F);

}
void ShaderProgram::use()
{
	glUseProgram(ID);
}

void ShaderProgram::setBool(const std::string& name, bool val)
{
	this->use();
	glUniform1i(glGetUniformLocation(ID, name.c_str()), val);

}

void ShaderProgram::setInt(const std::string& name, int val)
{
	this->use();

	glUniform1i(glGetUniformLocation(ID, name.c_str()), val);
}
void ShaderProgram::setFloat(const std::string& name, float val)
{
	this->use();

	glUniform1f(glGetUniformLocation(ID, name.c_str()), val);
}



void ShaderProgram::setArray(const std::string& name, int size, float* pointer)
{
	this->use();

	glUniform1fv(glGetUniformLocation(ID, name.c_str()), size, pointer);
}

void ShaderProgram::unuse()
{
	glUseProgram(0);
}

void ShaderProgram::setVector3f(const std::string& name, const Vector3f& vector3_f)
{
	use();
	glUniform3f(glGetUniformLocation(ID, name.c_str()), vector3_f.x, vector3_f.y, vector3_f.z);
}



void ShaderProgram::setMatrix4(const std::string& name, const glm::mat4& mat4)
{
	this->use();
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat4));
}


void ShaderProgram::addAttribute(std::string atribName, Attribute::Types type)
{
	this->AttributesRequiredList.push_back(atribName);
	this->AttributesRequiredMap.insert(std::pair<std::string, Attribute::Types>(atribName, type));
	this->vertexSize += type;
}

std::list<std::string>& ShaderProgram::getAttributeList()
{
	return this->AttributesRequiredList;
}

std::map<std::string, Attribute::Types>& ShaderProgram::getAttributeMap()
{
	return this->AttributesRequiredMap;
}




unsigned int ShaderProgram::getVertexSizeRequired()
{
	return this->vertexSize;
}

void ShaderProgram::setCamera(std::string  name, Camera* camera)
{
	use();
	if (camera == nullptr)
	{
		std::cerr << "Camera is null\n";
		throw std::runtime_error("Camera is null");
	}
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(camera->getCameraMatrix()));

}


std::string ShaderProgram::getTextFile(std::string file)
{
	std::stringstream stream;
	std::ifstream input;
	input.open(file);
	stream << input.rdbuf();
	return stream.str();
}


bool ShaderProgram::isLightAffeted()
{
	//TODO : 
	return true;
}
void ShaderProgram::applyLightData(Vector3f cameraPos)
{
	this->setVector3f("eyeP", cameraPos);
	this->setInt("light_data.amtofLight", Light::light_data.lightCounter);
	this->setFloat("light_data.ambientIntensity", Light::light_data.ambientIntensity);
	this->setVector3f("light_data.ambientColor", Light::light_data.ambientColor);
	std::string lightTypePrefix = "light_data.lightTypeData[";
	for(int i=0;i< Light::light_data.lightCounter;i++)
	{
	
			int type;
		float intensity;
			glm::vec3 color;
			glm::vec3 position;
			glm::vec3  direction;
		float angle;

		std::string name = lightTypePrefix + std::to_string(i) + "].";
		this->setInt(name+"type", Light::light_data.lightTypeData[i].type);
		this->setFloat(name + "intensity", Light::light_data.lightTypeData[i].intensity);
		this->setVector3f(name + "color", Light::light_data.lightTypeData[i].color);
		this->setVector3f(name + "position", Light::light_data.lightTypeData[i].position);
		this->setVector3f(name + "direction", Light::light_data.lightTypeData[i].direction);
			this->setFloat(name + "angle", Light::light_data.lightTypeData[i].angle);
	}
}