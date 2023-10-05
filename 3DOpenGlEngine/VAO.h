#pragma once
#include <iostream>
#include <glad/glad.h>
#include "VBO.h"

class VAO
{
public:
	unsigned int ID;

	VAO()
	{
		glGenVertexArrays(1, &ID);
		GLenum error = glGetError();
		}

	void linkAttrib(VBO* VBO, GLuint layout, GLuint nmOFElements, GLenum type, GLsizeiptr stride, int offset)
	{
		VBO->bind();
		glVertexAttribPointer(layout, nmOFElements, type, GL_FALSE, stride, (void*)offset);
		glEnableVertexAttribArray(layout);
		VBO->unbind();
	}

	void bind()
	{
		glBindVertexArray(ID);
	}

	void unbind()
	{
		glBindVertexArray(0);

	}

	void Delete()
	{
		glDeleteVertexArrays(1, &ID);
	}

};
