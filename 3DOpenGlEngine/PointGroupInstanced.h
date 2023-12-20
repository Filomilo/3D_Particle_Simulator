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
	std::shared_ptr<VBO> instancesVBO;

	void setInstanceGeo(std::shared_ptr<Polygonal> instanceGeo) {
		this->instanceGeo = instanceGeo;
	}





	void initInstancesVbo()
	{
		this->iniitVboUniversal(this->getVertexBuffer(), this->getVerteciesAmount(), this->getVertexSize(), this->instancesVBO, this->vao);
	}
	void initPolygonsVbo()
	{
		this->iniitVboUniversal(instanceGeo->getVertexBufferForMat(this->mat), instanceGeo->getVerteciesAmount(), instanceGeo->getVertexSizeForMat(this->mat), this->vbo,this->vao);
	}

	void iniitVao()
	{
		std::cout << "init vao" << std::endl;

		int verteciesAmt = this->instanceGeo->getVerteciesAmount();
		int vertexSize = this->instanceGeo->getVertexSize();

		std::map<std::string, Attribute::Types> attributesMap = mat->getAttributeMap();
		std::list<std::string> attributeList = mat->getAttributeList();

		int i = 0;
		int offset = 0;

		for (std::string name : attributeList)
		{
			Attribute::Types type = attributesMap[name];
			this->vao->linkAttrib(this->instanceGeo->vbo, i, type, GL_FLOAT, vertexSize * sizeof(float), offset);
			glEnableVertexAttribArray(i);
			std::cout << "glEnableVertexAttribArray(" << i << ")\n";
			i++;
			offset += type * sizeof(float);
		}
		this->vao->linkPointINstancePostion(instancesVBO, i, 3, GL_FLOAT, 3 * sizeof(float), 0);
		
	}

	void initParts()
	{
		std::cout << "--------------------------------------------------INSATEGEO\n\n(";
		initInstancesVbo();
		std::cout << "--------------------------------------------------INSATEGEO\n\n(";
		initPolygonsVbo();
		

		iniitVao();
		instanceGeo->iniitEBO();
	}




		void glDrawCall()
		{
		glDrawElementsInstanced(GL_TRIANGLES, instanceGeo->getTringlePointCount(), GL_UNSIGNED_INT, 0, this->points.size());
		//		glDrawElements(GL_TRIANGLES, instanceGeo->getTringlePointCount(), GL_UNSIGNED_INT, 0);
		//	this->instanceGeo->glDrawCall();
		//	glDrawElements(GL_TRIANGLES, instanceGeo->getTringlePointCount(), GL_UNSIGNED_INT, 0);

		}

		

	};

