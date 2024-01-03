/**
 * @file EBO.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file coanting ebo clas
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once
#include <glad/glad.h>
/**
 * @brief ebo clas fohanlig ebo buffer for opengll
 * 
 */
class EBO
{
public:
/**
 * @brief id used by openglgl to indetnify ebo handled by this cals isnance
 * 
 */
	unsigned int ID;
	/**
	 * @brief Construct a new EBO object
	 * 
	 * @param indeces 
	 * @param size 
	 * @param usage 
	 */
	EBO(GLuint* indeces, GLsizeiptr size, unsigned long int usage= GL_STATIC_DRAW)
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indeces, usage);
	}
/**
 * @brief bind ebo to 
 * 
 */
	void bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}
/**
 * @brief unbindsebo form opnelg
 * 
 */
	void unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}
/**
 * @brief detelt ebo buffer
 * 
 */
	void Delete()
	{
		glDeleteBuffers(1, &ID);
	}
	/**
	 * @brief updates ebo bugger
	 * 
	 * @param indeces 
	 * @param size 
	 * @param usage 
	 */
	void update(GLuint* indeces, GLsizeiptr size, unsigned long int usage = GL_DYNAMIC_DRAW)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indeces, usage);
		}


};
