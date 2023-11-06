#pragma once
#include "Material.h"
#include "Renderable.h"
#include "Transformable.h"
#include "VAO.h"

class GlObject :
	public Renderable,
	public Transformable
{
protected:
	std::unique_ptr<VAO> vao;
	std::shared_ptr<VBO> vbo;
	std::shared_ptr<Material> mat;

	int renderMode = GL_FILL;
	long int usage = GL_STATIC_DRAW;

	virtual GLfloat* getVertexBuffer() = 0;


	int getVertexSize()
	{
		return this->mat->getVertexSizeRequired();
	}


	virtual int getVerteciesAmount() = 0;
	virtual std::shared_ptr<Attribute> getVertexAttrib(int num, std::string attrib) = 0;


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




	void iniitVbo()
	{
		GLfloat* vertexBuffer = this->getVertexBuffer();
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

		this->vbo = std::make_unique <VBO>( vertexBuffer, this->getVerteciesAmount() * this->getVertexSize() * sizeof(float), usage);
		delete[] vertexBuffer;
	}

	void updateVbo()
	{
		GLfloat* vertexBuffer = this->getVertexBuffer();
		int verteciesAmt = this->getVerteciesAmount();
		int vertexSize = this->getVertexSize();


		vbo->bind();
		this->vbo ->update(vertexBuffer, this->getVerteciesAmount() * this->getVertexSize() * sizeof(float), usage);
		vbo->unbind();
		delete[] vertexBuffer;
	}

	void iniitVao()
	{

		int verteciesAmt = this->getVerteciesAmount();
		int vertexSize = this->getVertexSize();

		std::map<std::string, Attribute::Types> attributesMap = mat->getAttributeMap();
		std::list<std::string> attributeList = mat->getAttributeList();

		int i = 0;
		int offset = 0;
		
		for (std::string name : attributeList)
		{
			Attribute::Types type = attributesMap[name];
			this->vao->linkAttrib(vbo, i, type, GL_FLOAT, vertexSize * sizeof(float), offset);
			glEnableVertexAttribArray(i);
			//std::cout << "glEnableVertexAttribArray(" << i << ")\n";
			i++;
			offset += type * sizeof(float);
		}

	}

	virtual void bind()
	{
		this->vbo->bind();
		this->vao->bind();
	}
	virtual void unbind()
	{
		vao->unbind();
		vbo->unbind();
	}
	virtual void glDrawCall() = 0;

	void renderProc() override
	{
		glPolygonMode(GL_FRONT_AND_BACK, renderMode);
		if (mat != nullptr)
			mat->apply(this->getTransformationMatrix());
		bind();
		glDrawCall();
		unbind();
		mat->unapply();
	}
public:
	GlObject() : Transformable()
	{
			this->vao = std::make_unique<VAO>() ;
	}



	int get_render_mode() const
	{
		return renderMode;
	}

	void set_render_mode(int render_mode)
	{
		renderMode = render_mode;
	}
	void setMat(std::shared_ptr<Material>  mat)
	{
		this->mat = mat;
	}
	virtual void initParts()
	{
		iniitVbo();
		iniitVao();
	}
	void init()
	{
		initParts();
		unbind();
	}

	long get_usage() const
	{
		return usage;
	}

	void set_usage(long usage)
	{
		this->usage = usage;
	}
};

