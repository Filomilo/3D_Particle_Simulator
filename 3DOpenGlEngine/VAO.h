/**
 * @file VAO.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief a file containing class VAO
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once
#include <iostream>
#include <glad/glad.h>
#include "VBO.h"
/**
 * @brief a warpper for VAO
 * 
 * A class used tho help to manage VAO vertex array object contiang parameters fo VBo.
 * in other words it manages how data in VBO is intertreed by graphics card
 * 
 */
class VAO
{
public:
/**
 * @brief VAO id
 * 
 * id of VAo that is manged by this calss instance, it is auto genreted upoon class instance construciton
 */
	unsigned int ID;
/**
 * @brief Construct a new VAO object
 * 
 * a default constructor for VAO that cerated new id for opengl
 * 
 */
	VAO()
	{
		glGenVertexArrays(1, &ID);
		GLenum error = glGetError();
		}
/**
 * @brief a method that sepcifies attribute in vbo based on provied pramtes
 * 
 * @param vbo vertex buffer that cotaines data to be specifed
 * @param layout number of attribute to be sepcifed
 * @param nmOFElements number of elemtns in that attebute for example 2 for vectro 2f, 3 for vectro 3f and so on
 * @param type type of attribute , data type of attribute ussualy float
 * @param stride defiend if there bytes between atriubtes
 * @param offset defeind at what point veretx buffer starts
 */
	void linkAttrib(std::shared_ptr<VBO> vbo, GLuint layout, GLuint nmOFElements, GLenum type, GLsizeiptr stride, int offset)
	{
		vbo->bind();
		glVertexAttribPointer(layout, nmOFElements, type, GL_FALSE, stride, (void*)offset);
		//std::cout << "glVertexAttribPointer(" << layout << ", " << nmOFElements << ", " << type << ", " << " GL_FALSE" << ", " << stride << ", " << offset << ")\n";
		glEnableVertexAttribArray(layout);
		vbo->unbind();
	}

/**
 * @brief similar to toher link attribute however it uses ID instead of VBO object
 * 
 * @param vbo 
 * @param layout 
 * @param nmOFElements 
 * @param type 
 * @param stride 
 * @param offset 
 */
	void linkAttrib(GLuint vbo, GLuint layout, GLuint nmOFElements, GLenum type, GLsizeiptr stride, int offset)
	{
		glBindBuffer(GL_ARRAY_BUFFER,vbo);
		glVertexAttribPointer(layout, nmOFElements, type, GL_FALSE, stride, (void*)offset);
		//std::cout << "glVertexAttribPointer(" << layout << ", " << nmOFElements << ", " << type << ", " << " GL_FALSE" << ", " << stride << ", " << offset << ")\n";
		glEnableVertexAttribArray(layout);
		glBindBuffer(GL_ARRAY_BUFFER,0);
	}

	/**
	 * @brief a method that links instnace postion
	 * 
	 * its is simmlar ot link attributes howeber in definedd it atrribute as instance point, its currenly used in one instance rnedeirng and it snot suited for any ohter puprpose
	 * 
	 * @param vbo 
	 * @param layout 
	 * @param nmOFElements 
	 * @param type 
	 * @param stride 
	 * @param offset 
	 */
	void linkPointINstancePostion(std::shared_ptr<VBO> vbo, GLuint layout, GLuint nmOFElements, GLenum type, GLsizeiptr stride, int offset)
	{
		vbo->bind();
		glVertexAttribPointer(layout, nmOFElements, type, GL_FALSE, stride, (void*)offset);
		glEnableVertexAttribArray(layout);
		glVertexAttribDivisor(1, 1);
		vbo->unbind();
	}
/**
 * @brief bind vertex array id
 * 
 */
	void bind()
	{
		glBindVertexArray(ID);
	}
/**
 * @brief unbind veretx array id
 * 
 */
	void unbind()
	{
		glBindVertexArray(0);

	}
/**
 * @brief detle vertex array object
 * 
 */
	void Delete()
	{
		glDeleteVertexArrays(1, &ID);
	}

};
