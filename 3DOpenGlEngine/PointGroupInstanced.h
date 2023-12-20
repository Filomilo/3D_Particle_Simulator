#pragma once
#include "PointGroup.h"
#include "Polygonal.h"
class PointGroupInstanced :
	public PointGroup
{


public:
	PointGroupInstanced();
	~PointGroupInstanced();

	std::shared_ptr<Polygonal> instanceGeo;


	void setInstanceGeo(std::shared_ptr<Polygonal> instanceGeo) {
		this->instanceGeo = instanceGeo;
	}

	GLuint MBO;
	/*
	void iniitVbo()
	{
		GLfloat* vertexBuffer = instanceGeo->getVertexBuffer();
		int verteciesAmt = instanceGeo->getVerteciesAmount();
		int vertexSize = instanceGeo->getVertexSize();
		vao->bind();

		this->vbo = std::make_unique <VBO>(vertexBuffer, instanceGeo->getVerteciesAmount() * instanceGeo->getVertexSize() * sizeof(float), usage);
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
			std::cout << "glEnableVertexAttribArray(" << i << ")\n";
			i++;
			offset += type * sizeof(float);
		}

	
		glGenBuffers(1, &MBO);
		glBindBuffer(GL_ARRAY_BUFFER, MBO);
		GLfloat* mbo = this->getVertexBuffer();
		glBufferData(GL_ARRAY_BUFFER, this->points.size() * sizeof(GLfloat), mbo, GL_STATIC_DRAW);
		this->vao->linkAttrib(this->MBO, i, GL_FLOAT, GL_FLOAT, 3 * sizeof(float), offset);
		glEnableVertexAttribArray(i);
		glVertexAttribDivisor(i, 1);

		delete(mbo);

	}



	
		void updateVbo()
		{
			GLfloat* vertexBuffer = instanceGeo->getVertexBuffer();
			int verteciesAmt = this->getVerteciesAmount();
			int vertexSize = this->getVertexSize();
			vbo->bind();
			this->vbo->update(vertexBuffer, this->getVerteciesAmount() * this->getVertexSize() * sizeof(float), usage);
			vbo->unbind();
			delete[] vertexBuffer;
		}
		*/



	virtual void bind()
	{
		this->instanceGeo->bind();
	}
	virtual void unbind()
	{
		this->instanceGeo->unbind();
	}

		void glDrawCall()
		{
		//	glDrawElementsInstanced(GL_TRIANGLES, instanceGeo->getTringlePointCount(), GL_UNSIGNED_INT, 0, this->points.size());
		//		glDrawElements(GL_TRIANGLES, instanceGeo->getTringlePointCount(), GL_UNSIGNED_INT, 0);
			this->instanceGeo->glDrawCall();
		}

		

	};

