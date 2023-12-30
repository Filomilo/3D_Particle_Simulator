/**
 * @file Polygonal.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file containg polygonal class
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
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
#include <iostream>

/**
 * @brief class holding polygon data for opnegl
 * 
 * class holdign polgonal data used by oipengl to render object like cubes or planes
 * 
 */
class Polygonal :
    public PointGroup
{
private:

	friend class PointGroupInstanced;
	/**
	 * @brief elemnt buffer object for opengl
	 * 
	 * buffer hodling of elemtn s of object like duve faces
	 * 
	 */
	EBO* ebo;


/**
 * @brief list og Vertecis used by thi object
 * 
 */
	std::vector<std::shared_ptr<Vertex>> vertices;
	/**
	 * @brief list of face the object is made out of
	 * 
	 */
	std::vector<Face*> faces;

/**
 * @brief Get the Vertex Buffer For Mat object
 * 
 * creates vertec buffer with parametes in order of selected material
 * 
 * @param mat materila for wchich paramtes are needed
 * @return GLfloat* array of float for vertex buffer
 */
	GLfloat* getVertexBufferForMat(std::shared_ptr<Material> mat) override
	{
		GLfloat* arrayVbo = new float[this->getVerteciesAmount() * this->getVertexSize()];

		std::map<std::string, Attribute::Types> attributesMap = mat->getAttributeMap();
		std::list<std::string> attributeList = mat->getAttributeList();
		int index = 0;
		int vertIndex = 0;
		std::cout << "VErtxBuffer::" << std::endl;
		for (std::shared_ptr<Vertex> vertex : this->vertices)
		{
			for (std::string attribName : attributeList)
			{
				Attribute::Types attribType = attributesMap.find(attribName)->second;
				std::shared_ptr<Vector4f> attribVal = std::static_pointer_cast <Vector4f>(this->getVertexAttrib(vertIndex, attribName));
				for (int i = 0; i < attribType; i++)
				{
					arrayVbo[index++] = (*attribVal)[i];
				//	std::cout << (*attribVal)[i] << ", ";
				}


			}
		    //  std::cout<< vertIndex<<"/"<<this->vertices.size() << std::endl;
			vertIndex++;
		}

		return  arrayVbo;
	}

	/**
	 * @brief Get the Vertex Buffer object
	 * 
	 * retursn vertex buffer dat fot already apply material in object
	 * 
	 * @return GLfloat* 
	 */
	GLfloat* getVertexBuffer() override
	{

		return  getVertexBufferForMat(this->mat);
	}
	/**
	 * @brief Get the Vertecies Amount
	 * 
	 * retruns amount of vertecies the object is amde out of
	 * 
	 * @return int number of veretecies
	 */

	int getVerteciesAmount() override
	{
		return vertices.size();
	}


/**
 * @brief Get the Indecies Array object
 * 
 * retrunss array of indecies that object is made out of
 * 
 * @return unsigned* 
 */
	unsigned int* getIndeciesArray()
	{
		//std::cout <<"-------------------------------------------------------"<< this->getTringlePointCount() << std::endl << std::endl;
		int index = 0;
		unsigned int* eboArray = new  unsigned int[this->getTringlePointCount()];
		//std::cout << "ndeciesArray::" << std::endl;
		for (Face* face: this->faces)
		{
			std::vector<unsigned int> indecies = face->get_vertex_indecies();
			int firstIndex = indecies[0];
			
			for(int i=2;i<indecies.size();i++)
			{
				eboArray[index++] = firstIndex;
				eboArray[index++] = indecies[i-1];
				eboArray[index++] = indecies[i ];
			

				//std::cout << firstIndex << ", " << indecies[i-1] << ", " << indecies[i ] << std::endl;
			}
		}

		
	


		return eboArray;
	}


/**
 * @brief Get the Vertex Attrib object
 * 
 * returns vertex attribute, it first try to get attribute from veretx, if the is none it gets it from point, if there is none it get globaly and if thats did help i getsdeafult valur 9
 * 
 * @param num 
 * @param attrib 
 * @return std::shared_ptr<Attribute> 
 */
	std::shared_ptr<Attribute> getVertexAttrib(int num, std::string attrib) override
	{
		std::shared_ptr<Vertex> vertex = this->vertices.at(num);
		if (!vertex->isThereAttrib(attrib)) {
			std::shared_ptr<Point> pt = this->points.at(vertex->pointIndex);
			return pt->getAttribute(attrib);
		}
		return vertex->getAttribute(attrib);
	}
/**
 * @brief unbind polygonal object form opengl
 * 
 */
	void unbind() override
	{
		GlObject::unbind();
		ebo->unbind();
	}
	/**
	 * @brief bind poltgonal buffer to openl gl
	 * 
	 */
	void bind() override
	{
		GlObject::bind();
		this->ebo->bind();
	}

public:
/**
 * @brief Construct a new Polygonal object
 * 
 * basic empty constructor
 * 
 */
	Polygonal(): PointGroup()
	{
	
	}

	
/**
 * @brief add vertex for sepcifed poitn index
 * 
 * @param ptnum index of point
 */
	void addVertex(int ptnum)
	{
		std::shared_ptr<Vertex> vertex = std::make_shared<Vertex>(ptnum);
		this->vertices.push_back(vertex);
	}
/**
 * @brief add vertex fro specifed point index iwth provide d normal data
 * 
 * @param ptnum index of point
 * @param normals normal vector
 */
	void addVertex(int ptnum, Vector3f normals)
	{
		std::shared_ptr<Vertex> vertex = std::make_shared<Vertex>(ptnum, normals);
		this->vertices.push_back(vertex);
	}

/**
 * @brief add vertex at specifed point with porvided noraml vector and uv postion
 * 
 * @param ptnum index of point
 * @param normals normal vector of vertex
 * @param Uvs uv position of vertex
 */
	void addVertex(int ptnum, Vector3f normals, Vector2f Uvs)
	{
		std::shared_ptr<Vertex> vertex = std::make_shared<Vertex>(ptnum, normals, Uvs);
		this->vertices.push_back(vertex);
	}
/**
 * @brief adds face made out of provided point index
 * 
 * @param verteciesNumber list of vertecis maing face
 */
	void addFace(std::initializer_list<int> verteciesNumber)
	{
		Face* face = new Face;
		for (int val : verteciesNumber) {
			face->addPointINdex(val);
		}
		this->faces.push_back(face);
	}
	/**
	 * @brief crates muliple faces made out of prvide vertecie indecies
	 * 
	 * @param faces list of verteicies list making facs
	 */
	void addFaces(std::initializer_list<std::initializer_list<int> > faces)
	{
		for (std::initializer_list<int> verteciesNumber : faces)
		{
			this->addFace(verteciesNumber);
		}
	}

	/**
	 * @brief adds vertecies fform at point index list
	 * 
	 * @param indxs list of points to add vertecis upon
	 */
	void addVertecies(std::initializer_list<int> indxs)
	{
		for(int ptnb : indxs)
		{
			this->addVertex(ptnb);
		}
	}




/**
 * @brief intlizes ebo to opngl based data
 * 
 */
	void iniitEBO()

	{
		GLuint* indeciesBuffer = this->getIndeciesArray();
		/*
		for (int i = 0; i < this->getTringlePointCount(); i++)
		{
			//std::cout << indeciesBuffer[i] << ",";
			if (i % 3 == 2) {
				//std::cout << std::endl;
				if(i%1000==0)
				std::cout << i << "/" << this->getTringlePointCount() << "," << std::endl;;
			}
			
		}
		*/
		std::cout << "eboinit\n";
		this->ebo = new EBO((GLuint*)indeciesBuffer, this->getTringlePointCount() * sizeof(unsigned int));
		delete[] indeciesBuffer;
	}
	
/**
 * @brief initlize parat of objecy
 * 
 */
	void initParts() override
	{
		GlObject::initParts();
		iniitEBO();
	}


/**
 * @brief opengl call to draw object on screen
 * 
 */
	void glDrawCall() override
	{
	//std::cout << "polygonal rnder: " << this->vertices.size() << std::endl;;
		glDrawElements(GL_TRIANGLES, this->getTringlePointCount(), GL_UNSIGNED_INT, 0);

	}

/**
 * @brief adds face based on pointser to that face
 * 
 * @param face point to face to be added
 */
	void addFace(Face* face)
	{
		this->faces.push_back(face);
	}

/**
 * @brief adds face based indecies prvovided 
 * 
 * @param vector 
 */
	void addFace(const std::vector<int>& vector)
	{
		Face* newFace = new Face;
		for (int indx : vector)
		{
			newFace->addPointINdex(indx);
		}
		addFace(newFace);
	}


	/**
	 * @brief clea all geometry dta of instsnce
	 * 
	 */
	void cleanGeo() override
	{
		PointGroup::cleanGeo();


		vertices.clear();


		faces.clear();
	}
/**
 * @brief add rectangel in postion provided
 * 
 * @param left_upper_pos 
 * @param right_down_pos 
 * @param left_upper_uv 
 * @param right_down_uv 
 */
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
/**
 * @brief updates ebo data bsed on changes in object
 * 
 */
	void updateEbo()
	{


		GLuint* indeciesBuffer = this->getIndeciesArray();
		for (int i = 0; i < this->getTringlePointCount(); i++)
		{
			//std::cout << indeciesBuffer[i] << ",";
			//if (i % 3 == 2)
				//std::cout << std::endl;
		}
		this->ebo->update((GLuint*)indeciesBuffer, this->getTringlePointCount() * sizeof(unsigned int));

		delete[] indeciesBuffer;
	}
	public:
	/**
	 * @brief Get the Tringle Point Count object
	 * retruns amount of tringles making out the object
	 * 
	 * @return int 
	 */
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


		void addFullFace(std::vector<int> pointIndecies)
		{
			int currectnVrtexAmount = this->vertices.size();
			//std::cout << "size: " << this->vertices.size() << std::endl;
			Face* face = new Face();
			for (int pointindex : pointIndecies)
			{
				//std::cout << pointindex << ", ";
				this->addVertex(pointindex);
				face->addPointINdex(currectnVrtexAmount++);
			}
			this->addFace(face);
			//std::cout << std::endl;


		}

		void addFullFace(std::vector<int> pointIndecies, std::vector<Vector2f> uvs)
		{
			int currectnVrtexAmount = this->vertices.size();
			//std::cout << "size: " << this->vertices.size() << std::endl;
			Face* face = new Face();
			int i = 0;
			for (int pointindex : pointIndecies)
			{
			//	std::cout <<"pos: "<< pointindex << ", uv: "<< uvs.at(i)<<std::endl;
				this->addVertex(pointindex,Vector3f(0,0,0), uvs.at(i));
				face->addPointINdex(currectnVrtexAmount++);
				i++;
			}
			this->addFace(face);
			//std::cout << std::endl;


		}

		void addFullFace(std::vector<int> pointIndecies, std::vector<Vector2f> uvs, std::vector<Vector3f> ns)
		{
			int currectnVrtexAmount = this->vertices.size();
			//std::cout << "size: " << this->vertices.size() << std::endl;
			Face* face = new Face();
			int i = 0;
			for (int pointindex : pointIndecies)
			{
				//std::cout << "pos: " << pointindex << ", uv: " << uvs.at(i) << std::endl;
				this->addVertex(pointindex, ns.at(i), uvs.at(i));
				face->addPointINdex(currectnVrtexAmount++);
				i++;
			}
			this->addFace(face);
		//	std::cout << std::endl;


		}

};

