#pragma once


#include <stdexcept>
#include <string>
#include <glad/glad.h>

#include "Vector2f.h"


class Texture
{
protected:
	GLuint ID;
	int width;
	int height;
	int channels;
	void genTex(std::string file, int width, int height, int channels, int format);
	void genData(unsigned char* data, int width, int height, int channels, int format);
public:
	Texture(std::string file, int width, int height, int channels, int format = GL_RGB);
	Texture()
	{}
	Vector2f getSize()
	{
		return Vector2f(width, height);
	}

	void bind();
	static void unbind();
	
};
