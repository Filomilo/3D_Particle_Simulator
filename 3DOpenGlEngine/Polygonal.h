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
		std::vector<float> vbo;

		std::map<std::string, Attribute::Types> attributesMap = shader->getAttributeMap();
		std::list<std::string> attributeList = shader->getAttributeList();

		for (Vertex* vertex: this->vertices)
		{
			for (std::string attribName : attributeList)
			{
				Attribute::Types attribType = attributesMap.find(attribName)->second;
				Vector4f* attribVal =(Vector4f*) this->getVertexAttrib(vertex,attribName);
				for(int i=0;i< attribType;i++)
				{
					vbo.push_back((*attribVal)[i]);
					std::cout << (*attribVal)[i] << ", ";
				}


			}
			std::cout << std::endl;
		}
		float* arrayVbo = new float[vbo.size()];
		for(int i=0;i< vbo.size();i++)
		{
			arrayVbo[i] = vbo.at(i);
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


	int* getIndeciesArray()
	{
		std::cout << std::endl << std::endl;
		std::vector< int> ebo;
		for (Face* face: this->faces)
		{
			std::vector<unsigned int> indecies = face->get_vertex_indecies();
			int firstIndex = indecies[0];

			for(int i=1;i+1<indecies.size();i++)
			{
				ebo.push_back(firstIndex);
				ebo.push_back(indecies[i]);
				ebo.push_back(indecies[i+1]);

				std::cout << firstIndex << ", " << indecies[i] << ", " << indecies[i + 1] << std::endl;
			}
		}

		int* eboArray = new int[ebo.size()];
		for(int i=0;i<ebo.size();i++)
		{
			eboArray[i] = ebo.at(i);
		}


		return eboArray;
	}



	Attribute* getVertexAttrib(Vertex* vertex,std::string attrib)
	{
		Point* pt = this->points.at(vertex->pointIndex);
		return pt->getAttribute(attrib);
	}

public:


	void addPoints(std::initializer_list<std::initializer_list<float>> list)
	{
		for (std::initializer_list<float> pointValues: list)
		{
			Point * pt=new Point(pointValues);
			this->points.push_back(pt);
		}
	}

	void addFace(std::initializer_list<unsigned int> pointsIndecies)
	{
		Face* face = new Face();
		for(int index:  pointsIndecies)
		{
			face->addPointINdex(index);
		}
		
		this->faces.push_back(face);
	}

	void addVertecies(std::initializer_list<unsigned int > pointsIndecies)
	{
		for (unsigned int index : pointsIndecies)
		{
			this->vertices.push_back(new Vertex(index));
		}
	}

	void addVertex(int pointIndex, std::initializer_list<float> normals, std::initializer_list<float> uvs)
	{
		Vertex* vertex=new Vertex(pointIndex);
		
		Vector3f* N = new Vector3f();
		Vector2f* Uv = new Vector2f();
		int i= 0;
		for (float normal: normals)
		{
			N[i++] = normal;
		}
		i = 0;
		for (float uv : uvs)
		{
			Uv[i++] = uv;
		}
		vertex->setAttribute("N",N);
		vertex->setAttribute("Uv", Uv);
		
		this->vertices.push_back(vertex);

		
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
		int* indeciesBuffer = this->getIndeciesArray();



		//std::cout << "Test: " << this->getVerteciesAmount()*this->getVertexSize()*sizeof(float)<< "\n";


		this->vao = new VAO();
		vao->bind();

		this->vbo = new VBO(vertexBuffer, this->getVerteciesAmount() * this->getVertexSize() * sizeof(float));
		
	


		std::map<std::string, Attribute::Types> attributesMap = shader->getAttributeMap();
		std::list<std::string> attributeList = shader->getAttributeList();
		this->ebo = new EBO((GLuint*)indeciesBuffer, this->getTringlePointCount() * sizeof(int));



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
	


	}

	void renderProc() override
	{
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		shader->use();
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

