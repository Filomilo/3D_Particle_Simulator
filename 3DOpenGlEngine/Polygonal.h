#pragma once


#include <list>

#include "EBO.h"
#include "Renderable.h"
#include "Transformable.h"

#include "Face.h"
#include "glObject.h"
#include "Material.h"
#include "Vertex.h"
#include "Point.h"
#include "PointGroupObject.h"
#include "VAO.h"
#include "Vector4f.h"

class Polygonal  :
	public PointGroupObject
{
private:


	EBO* ebo;





	

	std::vector<Vertex*> vertices;
	std::vector<Face*> faces;

	

	float* getVertexBuffer()
	{
		float* arrayVbo = new float[this->getVerteciesAmount()*this->getVertexSize()];

		std::map<std::string, Attribute::Types> attributesMap = mat->getAttributeMap();
		std::list<std::string> attributeList = mat->getAttributeList();
		int index = 0;
		int vertexIndex = 0;
		for (Vertex* vertex: this->vertices)
		{
			for (std::string attribName : attributeList)
			{
				Attribute::Types attribType = attributesMap.find(attribName)->second;
				Vector4f* attribVal =(Vector4f*) this->getVertexAttrib(vertexIndex,attribName);
				for(int i=0;i< attribType;i++)
				{
					arrayVbo[index++] = (*attribVal)[i];
					std::cout << (*attribVal)[i] << ", ";
				}


			}
			std::cout << std::endl;
			vertexIndex++;
		}

		return  arrayVbo;
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

	

public:

	Polygonal()
	{}


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
	void prepEBO()
	{
		GLuint* indeciesBuffer = this->getIndeciesArray();
		std::cout << "\n\nindeciesBuffer: \n";
		for (int i = 0; i < this->getTringlePointCount(); i++)
		{
			std::cout << indeciesBuffer[i] << ",";
			if (i % 3 == 2)
				std::cout << std::endl;
		}
		this->ebo = new EBO((GLuint*)indeciesBuffer, this->getTringlePointCount() * sizeof(unsigned int));
		delete[] indeciesBuffer;
	}

	void iniit()
	{
		glObject::iniit();
		prepEBO();

		vao->unbind();
		vbo->unbind();
		ebo->unbind();
	
		

	}

	void renderProc() override
	{

		glPolygonMode(GL_FRONT_AND_BACK, renderMode);
		if(mat!=nullptr)
		mat->apply(this->getTransformationMatrix());
		this->ebo->bind();
		this->vao->bind();
		glDrawElements(GL_TRIANGLES, this->getTringlePointCount() , GL_UNSIGNED_INT, 0);
		this->vao->unbind();
		this->ebo->unbind();
	}

	void setMat(Material* mat)
	{
		this->mat = mat;
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


	


	int get_render_mode() const
	{
		return renderMode;
	}

	void set_render_mode(int render_mode)
	{
		renderMode = render_mode;
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

	void addVertecies(std::initializer_list<int> indxs)
	{
		for (int ptnb : indxs)
		{
			this->addVertex(ptnb);
		}
	}


	int getVerteciesAmount() override
	{
		return vertices.size();
	}

};

