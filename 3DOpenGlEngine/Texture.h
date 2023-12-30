/**
 * @file Texture.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file conaitng Texture class
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once


#include <stdexcept>
#include <string>
#include <glad/glad.h>

#include "Vector2f.h"

/**
 * @brief class texture magnaing openg gl texture
 * 
 * class used to help with amganig laoded texture in opengl
 * 
 */
class Texture
{
protected:
/**
 * @brief open gl texture id
 * 
 */
	GLuint ID;
	/**
	 * @brief width of texture
	 * 
	 */
	int width;
	/**
	 * @brief height of texture
	 * 
	 */
	int height;
	/**
	 * @brief bit channels of texutre
	 * 
	 */
	int channels;
	/**
	 * @brief mrthod used for genratign texture 
	 * 
	 * @param file file conating texture
	 * @param width width of texture
	 * @param height height of texture
	 * @param channels channels in texture image
	 * @param format format of texture
	 */
	void genTex(std::string file, int width, int height, int channels, int format);
	/**
	 * @brief genertes texture data based ob bytes
	 * 
	 * @param data bytes conating texture data
	 * @param width width of texture
	 * @param height height of texture
	 * @param channels channels in texture image
	 * @param format format of texture
	 */
	void genData(unsigned char* data, int width, int height, int channels, int format);
public:
/**
 * @brief Construct a new Texture object
 * 
 * main constructor of texture
 * 
	 * @param file file conating texture
	 * @param width width of texture
	 * @param height height of texture
	 * @param channels channels in texture image
	 * @param format format of texture
	 */
	Texture(std::string file, int width, int height, int channels, int format = GL_RGB);
	/**
	 * @brief Construct a new Texture object
	 * 
	 * basic empty constructor
	 */
	Texture()
	{}
	/**
	 * @brief Get the Size object
	 * 
	 * retruns vector with size data about texture
	 * 
	 * @return Vector2f 
	 */
	Vector2f getSize()
	{
		return Vector2f(width, height);
	}
/**
 * @brief bind texture to opnegl
 * 
 */
	void bind();
	/**
	 * @brief binds empty texture to opengl
	 * 
	 */
	static void unbind();
	
};
