/**
 * @file VBO.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file coniatng class implematino of VBO (vertex buffer object )
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once
#include <iostream>
#include <glad/glad.h>
/**
 * @brief cass wraping functinlaity of VBO for opengl
 * 
 * a class helpign with mangaing vertexb buffer used in opengl rendering to send dat to graphics card
 */
class VBO
{
public:
/**
 * @brief Vertex buffer id
 * 
 * id of vertex buffer that is mannagnt by this class instance, ID is geenretd by opengl function inside constructor
 */
	unsigned int ID;
	/**
	 * @brief Construct a new VBO object
	 * 
	 * A constructor fro vbo that gets vertecis array and its size and construct vertex buffer based on  that data
	 * 
	 * @param vertieces pointer to array conatineg vertex buffer data to be placed inside VBO
	 * @param size  size fo cretex bffer array data
	 * @param usage udage type used by opengl to determin if its updated many time or it only a few times and optimes acrodigly
	 */
	VBO(GLfloat* vertieces, GLsizeiptr size, unsigned long int usage= GL_STATIC_DRAW)
	{
		glGenBuffers(1, &ID);
		update(vertieces, size, usage);
	}
/**
 * @brief a method that send vertex buffer data to vertex buffer object
 * 
 * @param vertieces pointer to array conatineg vertex buffer data to be placed inside VBO
 * @param size  size fo cretex bffer array data
 * @param usage udage type used by opengl to determin if its updated many time or it only a few times and optimes acrodigly
 */
	void update(GLfloat* vertieces, GLsizeiptr size, unsigned long int usage = GL_STATIC_DRAW)
	{
		
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, size, vertieces, usage);
	
	}
/**
 * @brief a wrapper for glBindBUffer
 * 
 */
	void bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);
			}
/**
 * @brief a warpper taht uning vbo in opengl
 * 
 */
	void unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
/**
 * @brief deletes vertex buffer object
 * 
 */
	void Delete()
	{
		glDeleteBuffers(1, &ID);
	}

};