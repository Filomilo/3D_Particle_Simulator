#pragma once
#include <vector>
#include <glad/glad.h>

#include "Material.h"
#include "Point.h"
#include "Renderable.h"
#include "Transformable.h"
#include "VAO.h"
#include "VBO.h"
#include "Vertex.h"

class glObject :
	public Renderable,
	public Transformable
{
protected:
	Material* mat;
	VAO* vao;
	VBO* vbo;


	int renderMode = GL_FILL;


	virtual void bind()
	{
		glPolygonMode(GL_FRONT_AND_BACK, renderMode);
		if (mat != nullptr)
			mat->apply(this->getTransformationMatrix());
		this->vao->bind();
	}

	virtual void unbind()
	{
		this->vao->unbind();

	}

	virtual void glRender() = 0;

public:
	 glObject() = default;


	int getVertexSize()
	{
		return this->mat->getVertexSizeRequired();
	}
	virtual int getVerteciesAmount()=0;

	std::map<std::string, Attribute::Types> getMapOfAttributes()
	{
		return this->mat->getAttributeMap();
	}

	std::list<std::string> getListOfAttributes()
	{
		return this->mat->getAttributeList();
	}

	int getSizeOfVertex()
	{
		return this->mat->getVertexSizeRequired();
	}


	virtual void iniit()
	{
		this->vao = new VAO();
		vao->bind();
		prepVBO();
		prepVao();
	}
	virtual Attribute* getVertexAttrib(int num, std::string attrib) = 0;
	virtual  float* getVertexBuffer() = 0;


	void prepVao()
	{
		int i = 0;
		int offset = 0;

		std::map<std::string, Attribute::Types> attributesMap = mat->getAttributeMap();
		std::list<std::string> attributeList = mat->getAttributeList();
		int vertexSize = getSizeOfVertex();

		for (std::string name : attributeList)
		{
			Attribute::Types type = attributesMap[name];
			this->vao->linkAttrib(vbo, i, type, GL_FLOAT, vertexSize * sizeof(float), offset);
			glEnableVertexAttribArray(i);
		//	std::cout << "glEnableVertexAttribArray(" << i << ")\n";
			i++;
			offset += type * sizeof(float);
		}

	}

	void prepVBO()
	{
		float* vertexBuffer = getVertexBuffer();

		int verteciesAmt = this->getVerteciesAmount();
		int vertexSize = this->getVertexSize();
		/*
		for (int i = 0; i < verteciesAmt * vertexSize; i++)
		{
			std::cout << vertexBuffer[i] << ",";
			if (i % vertexSize == vertexSize - 1)
				std::cout << std::endl;
		}
		*/
		vao->bind();

		this->vbo = new VBO(vertexBuffer, this->getVerteciesAmount() * this->getVertexSize() * sizeof(float));
		delete[] vertexBuffer;
	}

	int get_render_mode() const
	{
		return renderMode;
	}

	void set_render_mode(int render_mode)
	{
		renderMode = render_mode;
	}

	void setMat(Material* mat)
	{
		this->mat = mat;
	}



	virtual void renderProc()
	{
		bind();
		glRender();
		unbind();
	}
};

