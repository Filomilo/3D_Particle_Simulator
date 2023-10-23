#pragma once
#include <glad/glad.h>

class EBO
{
public:
	unsigned int ID;
	EBO(GLuint* indeces, GLsizeiptr size, unsigned long int usage= GL_STATIC_DRAW)
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indeces, usage);
	}

	void bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}

	void unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

	void Delete()
	{
		glDeleteBuffers(1, &ID);
	}
	void update(GLuint* indeces, GLsizeiptr size, unsigned long int usage = GL_DYNAMIC_DRAW)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indeces, usage);
		}


};
