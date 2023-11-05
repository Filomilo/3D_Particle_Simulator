#pragma once


#include <list>

#include "EBO.h"
#include "Renderable.h"
#include "Transformable.h"

#include "Face.h"
#include "GlObject.h"
#include "Material.h"
#include "Vertex.h"
#include "Point.h"
#include "PointGroup.h"
#include "VAO.h"
#include "Vector4f.h"

class Polygonal :
    public PointGroup
{
private:


	EBO* ebo;



	std::vector<Vertex*> vertices;
	std::vector<Face*> faces;



	float* getVertexBuffer() override
	{
		float* arrayVbo = new float[this->getVerteciesAmount()*this->getVertexSize()];

		std::map<std::string, Attribute::Types> attributesMap = mat->getAttributeMap();
		std::list<std::string> attributeList = mat->getAttributeList();
		int index = 0;
		int vertIndex = 0;
		std::cout << "VErtxBuffer::" << std::endl;
		for (Vertex* vertex: this->vertices)
		{
			for (std::string attribName : attributeList)
			{
				Attribute::Types attribType = attributesMap.find(attribName)->second;
				Vector4f* attribVal =(Vector4f*) this->getVertexAttrib(vertIndex,attribName);
				for(int i=0;i< attribType;i++)
				{
					arrayVbo[index++] = (*attribVal)[i];
					std::cout << (*attribVal)[i] << ", ";
				}


			}
			std::cout << std::endl;
			vertIndex++;
		}

		return  arrayVbo;
	}

	int getVerteciesAmount() override
	{
		return vertices.size();
	}
	int getTringlePointCount()
	{
		int numbers = 0;
		for (Face* fc : this->faces)
		{
			numbers += 3 * (fc->get_vertex_indecies().size() - 2);
			//std::cout << "numbers:: " << numbers << std::endl;
		}
		return numbers;
	}


	unsigned int* getIndeciesArray()
	{
		std::cout <<"-------------------------------------------------------"<< this->getTringlePointCount() << std::endl << std::endl;
		int index = 0;
		unsigned int* eboArray = new  unsigned int[this->getTringlePointCount()];
		std::cout << "ndeciesArray::" << std::endl;
		for (Face* face: this->faces)
		{
			std::vector<unsigned int> indecies = face->get_vertex_indecies();
			int firstIndex = indecies[0];
			
			for(int i=2;i<indecies.size();i++)
			{
				eboArray[index++] = firstIndex;
				eboArray[index++] = indecies[i-1];
				eboArray[index++] = indecies[i ];
			

				std::cout << firstIndex << ", " << indecies[i-1] << ", " << indecies[i ] << std::endl;
			}
		}

		
	


		return eboArray;
	}



	Attribute* getVertexAttrib(int num, std::string attrib) override
	{
		Vertex* vertex = this->vertices.at(num);
		if (!vertex->isThereAttrib(attrib)) {
			Point* pt = this->points.at(vertex->pointIndex);
			return pt->getAttribute(attrib);
		}
		return vertex->getAttribute(attrib);
	}

	void unbind() override
	{
		GlObject::unbind();
		ebo->unbind();
	}
	void bind() override
	{
		GlObject::bind();
		this->ebo->bind();
	}

public:

	Polygonal(): PointGroup()
	{
	
	}

	

	void addVertex(int ptnum)
	{
		Vertex* vertex = new Vertex(ptnum);
		this->vertices.push_back(vertex);
	}

	void addVertex(int ptnum, Vector3f normals)
	{
		Vertex* vertex = new Vertex(ptnum, normals);
		this->vertices.push_back(vertex);
	}


	void addVertex(int ptnum, Vector3f normals, Vector2f Uvs)
	{
		Vertex* vertex = new Vertex(ptnum, normals, Uvs);
		this->vertices.push_back(vertex);
	}

	void addFace(std::initializer_list<int> verteciesNumber)
	{
		Face* face = new Face;
		for (int val : verteciesNumber) {
			face->addPointINdex(val);
		}
		this->faces.push_back(face);
	}
	void addFaces(std::initializer_list<std::initializer_list<int> > faces)
	{
		for (std::initializer_list<int> verteciesNumber : faces)
		{
			this->addFace(verteciesNumber);
		}
	}
	void addVertecies(std::initializer_list<int> indxs)
	{
		for(int ptnb : indxs)
		{
			this->addVertex(ptnb);
		}
	}





	void iniitEBO()

	{
		GLuint* indeciesBuffer = this->getIndeciesArray();
		for (int i = 0; i < this->getTringlePointCount(); i++)
		{
			std::cout << indeciesBuffer[i] << ",";
			if (i % 3 == 2)
				std::cout << std::endl;
		}
		this->ebo = new EBO((GLuint*)indeciesBuffer, this->getTringlePointCount() * sizeof(unsigned int));
		delete[] indeciesBuffer;
	}
	

	void initParts() override
	{
		GlObject::initParts();
		iniitEBO();
	}



	void glDrawCall() override
	{
		glDrawElements(GL_TRIANGLES, this->getTringlePointCount(), GL_UNSIGNED_INT, 0);

	}


	void addFace(Face* face)
	{
		this->faces.push_back(face);
	}

	void addFace(const std::vector<int>& vector)
	{
		Face* newFace = new Face;
		for (int indx : vector)
		{
			newFace->addPointINdex(indx);
		}
		addFace(newFace);
	}


	
	void cleanGeo() override
	{
		PointGroup::cleanGeo();
		for(Vertex* element: vertices)
		{
			delete element;
		}
		vertices.clear();

		for (Face* element : faces)
		{
			delete element;
		}
		faces.clear();
	}

	void addRect(const Vector2f& left_upper_pos, const Vector2f& right_down_pos, const Vector2f& left_upper_uv, const Vector2f& right_down_uv)
	{
		int amountOfPOints = this->points.size();
		this->addPoint(left_upper_pos.x, left_upper_pos.y,0);
		this->addPoint(right_down_pos.x, left_upper_pos.y, 0);
		this->addPoint(right_down_pos.x, right_down_pos.y, 0);
		this->addPoint(left_upper_pos.x, right_down_pos.y, 0);

		this->addVertex(amountOfPOints + 0, { 0.000000, 1.000000 ,0.000000 }, { left_upper_uv.x, left_upper_uv.y });
		this->addVertex(amountOfPOints + 1, { 0.000000, 1.000000, 0.000000 }, { right_down_uv.x ,left_upper_uv.y });
		this->addVertex(amountOfPOints + 2, { 0.000000, 1.000000 ,0.000000 }, { right_down_uv.x,right_down_uv.y });
		this->addVertex(amountOfPOints + 3, { 0.000000, 1.000000, 0.000000 }, { left_upper_uv.x, right_down_uv.y });

		this->addFace({ amountOfPOints + 0,amountOfPOints + 1,amountOfPOints + 2,amountOfPOints + 3 });

	}

protected:
	void updateEbo()
	{


		GLuint* indeciesBuffer = this->getIndeciesArray();
		for (int i = 0; i < this->getTringlePointCount(); i++)
		{
			std::cout << indeciesBuffer[i] << ",";
			if (i % 3 == 2)
				std::cout << std::endl;
		}
		this->ebo->update((GLuint*)indeciesBuffer, this->getTringlePointCount() * sizeof(unsigned int));

		delete[] indeciesBuffer;
	}

};

