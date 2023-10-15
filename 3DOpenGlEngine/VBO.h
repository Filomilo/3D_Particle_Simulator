#pragma once
#include <iostream>
#include <glad/glad.h>
class VBO
{
public:
	unsigned int ID;
	VBO(GLfloat* vertieces, GLsizeiptr size, unsigned long int usage= GL_STATIC_DRAW)
	{
		glGenBuffers(1, &ID);
		update(vertieces, size, usage);
	}

	void update(GLfloat* vertieces, GLsizeiptr size, unsigned long int usage = GL_STATIC_DRAW)
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, size, vertieces, usage);
	}

	void bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);
			}

	void unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Delete()
	{
		glDeleteBuffers(1, &ID);
	}

};