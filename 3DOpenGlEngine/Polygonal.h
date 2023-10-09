#pragma once


#include "EBO.h"
#include "Renderable.h"
#include "Transformable.h"

#include "Face.h"
#include "Vertex.h"
#include "Point.h"
#include "VAO.h"
#include "ShaderProgram.h"
#include "Vector4f.h"

class Polygonal :
    public Renderable,
	public Transformable
{
private:

	VAO* vao;
	EBO* ebo;
	VBO* vbo;

	ShaderProgram* shader;


	std::vector<Point*> points;
	std::vector<Vertex*> vertices;
	std::vector<Face*> faces;


	float* getVertexBuffer()
	{
		float* arrayVbo = new float[this->getVerteciesAmount()*this->getVertexSize()];

		std::map<std::string, Attribute::Types> attributesMap = shader->getAttributeMap();
		std::list<std::string> attributeList = shader->getAttributeList();
		int index = 0;
		for (Vertex* vertex: this->vertices)
		{
			for (std::string attribName : attributeList)
			{
				Attribute::Types attribType = attributesMap.find(attribName)->second;
				Vector4f* attribVal =(Vector4f*) this->getVertexAttrib(vertex,attribName);
				for(int i=0;i< attribType;i++)
				{
					arrayVbo[index++] = (*attribVal)[i];
					std::cout << (*attribVal)[i] << ", ";
				}


			}
			std::cout << std::endl;
		}

		return  arrayVbo;
	}

	int getVertexSize()
	{
		return this->shader->getVertexSizeRequired();
	}
	int getVerteciesAmount()
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



	Attribute* getVertexAttrib(Vertex* vertex,std::string attrib)
	{
		Point* pt = this->points.at(vertex->pointIndex);
		return pt->getAttribute(attrib);
	}

public:

	Polygonal(): Transformable()
	{}

	void addPoint(Point* x)
	{
		this->points.push_back(x);
	}
	void addPoint(Point pt)
	{
		Vector3f* Pos = (Vector3f*)pt.getAttribute("P");
		Point* point = new Point(Pos->x, Pos->y, Pos->z);

		this->addPoint(point);
	}


	void addPoint(float x, float y, float z)
	{
		this->addPoint(new Point(x, y, z));
	}
	void addPoint(std::initializer_list<float> coordinates)
	{
		Point* pt = new Point(coordinates);
		this->addPoint(pt);
	}
	void addPoints(std::initializer_list<std::initializer_list<float> > coordinates)
	{
		for (std::initializer_list<float> coord : coordinates)
		{
			this->addPoint(coord);
		}
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
	void addVertex(int ptnum, Vector3f normals, Vector3f Uvs)
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


	std::map<std::string,Attribute::Types> getMapOfAttributes()
	{
		return this->shader->getAttributeMap();
	}

	std::list<std::string> getListOfAttributes()
	{
		return this->shader->getAttributeList();
	}

	int getSizeOfVertex()
	{
		return this->shader->getVertexSizeRequired();
	}

	void initilizePolygonal()
	{
		float* vertexBuffer = this->getVertexBuffer();
		GLuint* indeciesBuffer = this->getIndeciesArray();



		//std::cout << "Test: " << this->getVerteciesAmount()*this->getVertexSize()*sizeof(float)<< "\n";
		std::cout << "VertexBuffer: \n";
		for(int i=0;i<  this->getVerteciesAmount() * this->getVertexSize();i++)
		{
			std::cout << vertexBuffer[i] << ",";
			if (i % 3==2)
				std::cout << std::endl;
		}


		std::cout << "\n\nindeciesBuffer: \n";
		for (int i = 0; i < this->getTringlePointCount(); i++)
		{
			std::cout << indeciesBuffer[i] << ",";
			if (i % 3 == 2)
				std::cout << std::endl;
		}
		this->vao = new VAO();
		vao->bind();

		this->vbo = new VBO(vertexBuffer, this->getVerteciesAmount() * this->getVertexSize() * sizeof(float));
		
	


		std::map<std::string, Attribute::Types> attributesMap = shader->getAttributeMap();
		std::list<std::string> attributeList = shader->getAttributeList();
		this->ebo = new EBO((GLuint*)indeciesBuffer, this->getTringlePointCount() * sizeof(unsigned int));



		int i = 0;
		int offset = 0;
		for(std::string name: attributeList)
		{
			Attribute::Types type = attributesMap[name];
			this->vao->linkAttrib(vbo, i++, type, GL_FLOAT, type * sizeof(float), offset);
			offset += type * sizeof(float);
		}

		vao->unbind();
		vbo->unbind();
		ebo->unbind();
	
		delete[] vertexBuffer;
		delete[] indeciesBuffer;

	}

	void renderProc() override
	{
		//this->rotateY(0.01);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//this->set_scale(cos(clock() / 1000.0f)/3);
		shader->use();
		shader->setMatrix4("model", this->getTransformationMatrix());
		this->ebo->bind();
		this->vao->bind();
		glDrawElements(GL_TRIANGLES, this->getTringlePointCount() , GL_UNSIGNED_INT, 0);
		this->vao->unbind();
		this->ebo->unbind();
	}

	void setShader(ShaderProgram* shader)
	{
		this->shader = shader;
	}
};

