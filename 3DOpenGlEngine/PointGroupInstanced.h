/**
 * @file PointGroupInstanced.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file conaitng Point group instanced class
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include "PointGroup.h"
#include "Polygonal.h"
/**
 * class for mangaing point group pwih additon of insaicng polyognla model in postion of points.
 */
class PointGroupInstanced :
	public PointGroup
{


public:
	PointGroupInstanced();
	~PointGroupInstanced();
	/**
	 * .geometry instanced across points
	 */
	std::shared_ptr<Polygonal> instanceGeo;
	/**
	 * VBO buffer of instanced greomntry.
	 */
	std::shared_ptr<VBO> instancesVBO;
	/**
	 * a emthod that let you set geoemtry that is goinf to be instanced acrsos points.
	 * 
	 * \param instanceGeo
	 */
	void setInstanceGeo(std::shared_ptr<Polygonal> instanceGeo) {
		this->instanceGeo = instanceGeo;
	}




	/**
	 * initlize vbo of instance points
	 * 
	 */
	void initInstancesVbo()
	{
		this->iniitVboUniversal(this->getVertexBuffer(), this->getVerteciesAmount(), this->getVertexSize(), this->instancesVBO, this->vao);
	}
	/**
	 * .intilzes vbo of instance grometry
	 * 
	 */
	void initPolygonsVbo()
	{
		this->iniitVboUniversal(instanceGeo->getVertexBufferForMat(this->mat), instanceGeo->getVerteciesAmount(), instanceGeo->getVertexSizeForMat(this->mat), this->vbo,this->vao);
	}
	/**
	 * initlizes vertex atrribute buffer.
	 * 
	 */
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

	/**
	 * .intilizes all parts of point group instanced
	 * 
	 */
	void initParts()
	{
		//std::cout << "--------------------------------------------------INSATEGEO\n\n(";
		initInstancesVbo();
		//std::cout << "--------------------------------------------------INSATEGEO\n\n(";
		initPolygonsVbo();
		

		iniitVao();
		instanceGeo->iniitEBO();
	}
	/**
	 * updates points postion in vbo bufffer.
	 * 
	 */
	void updateVboInstanced()
	{
		this->updateVboUNiversal(this->getVertexBufferForMat(this->mat), this->getVerteciesAmount(), this->getVertexSizeForMat(this->mat),this->usage, this->instancesVBO, this->vao);

	
		
	}


	/**
	 * call for oprngl function that drwaws instaced geometry.
	 * 
	 */
		void glDrawCall()
		{
		glDrawElementsInstanced(GL_TRIANGLES, instanceGeo->getTringlePointCount(), GL_UNSIGNED_INT, 0, this->points.size());
		//		glDrawElements(GL_TRIANGLES, instanceGeo->getTringlePointCount(), GL_UNSIGNED_INT, 0);
		//	this->instanceGeo->glDrawCall();
		//	glDrawElements(GL_TRIANGLES, instanceGeo->getTringlePointCount(), GL_UNSIGNED_INT, 0);

		}

		

	};

