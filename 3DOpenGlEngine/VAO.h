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

	void linkAttrib(std::shared_ptr<VBO> vbo, GLuint layout, GLuint nmOFElements, GLenum type, GLsizeiptr stride, int offset)
	{
		vbo->bind();
		glVertexAttribPointer(layout, nmOFElements, type, GL_FALSE, stride, (void*)offset);
		//std::cout << "glVertexAttribPointer(" << layout << ", " << nmOFElements << ", " << type << ", " << " GL_FALSE" << ", " << stride << ", " << offset << ")\n";
		glEnableVertexAttribArray(layout);
		vbo->unbind();
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
