#pragma once


#include <stdexcept>
#include <string>
#include <glad/glad.h>



class Texture
{
private:
	GLuint ID;
	int width;
	int height;
	int channels;

public:
	Texture(std::string file, int width, int height, int channels);



	void bind();
	void unbind();
	
};
