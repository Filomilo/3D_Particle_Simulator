/**
 * @file PointGroup.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief File containg POintGroup class
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include "GlObject.h"
#include "Point.h"

/**
 * @brief class object made out of points
 * 
 */
class PointGroup :
    public GlObject
{
protected:
/**
 * @brief vector conating list of points
 * 
 */
    std::vector<std::shared_ptr<Point>> points;
/**
 * @brief Get the Vertex Attrib object
 * 
 * @param num index of vertex
 * @param attrib string representing attibute you want to retrive
 * @return std::shared_ptr<Attribute> 
 */
	std::shared_ptr<Attribute> getVertexAttrib(int num, std::string attrib) override
	{
		std::shared_ptr<Point> pt = this->points.at(num);
		if (!pt->isThereAttrib(attrib)) {
			return pt->getAttribute(attrib);
		}
		return pt->getAttribute(attrib);
	}
/**
 * @brief Get the Vertecies Amount object
 * 
 * returns amount verteies(int this case ponints )
 * 
 * @return int number of verteic
 */
	int getVerteciesAmount() override
	{
		return points.size();
	}

/**
 * @brief Get the Vertex Buffer For Mat object
 * 
 * create and retrunns vertex buffer for thid object wit attirubte specifed in privoided amterial
 * 
 * @param mat material for which you want to create vertex buffer
 * @return GLfloat* 
 */
	GLfloat* getVertexBufferForMat(std::shared_ptr<Material> mat) override
	{
		GLfloat* arrayVbo = new float[this->getVerteciesAmount() * this->getVertexSize()];

		std::map<std::string, Attribute::Types> attributesMap = mat->getAttributeMap();
		std::list<std::string> attributeList = mat->getAttributeList();
		int index = 0;
		int vertIndex = 0;
		for (std::shared_ptr<Point> vertex : this->points)
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
			//std::cout << std::endl;
			vertIndex++;
		}

		return  arrayVbo;
	}
/**
 * @brief Get the Vertex Buffer object
 * 
 * createa and returns verrtex buffer point group for already applied dmaterial
 * 
 * @return GLfloat* 
 */
	GLfloat* getVertexBuffer() override
	{
		
		return  getVertexBufferForMat(this->mat);
	}
	/**
	 * @brief oprn gl draw cal draw points
	 * 
	 */
	void glDrawCall() override
	{
		glDrawArrays(GL_POINTS, 0, getVerteciesAmount());
	}

public:
    PointGroup(): GlObject()
    {}

/**
 * @brief add point to point group
 * 
 * @param x shared pointer to point to be added
 */
	void addPoint(std::shared_ptr<Point> x)
	{
		this->points.push_back(x);
	}
	/**
	 * @brief adds point to point group
	 * 
	 * @param pt point to be added
	 */
	void addPoint(Point pt)
	{
		 std::shared_ptr<Vector3f> Pos = std::dynamic_pointer_cast <Vector3f>(pt.getAttribute("P"));
		std::shared_ptr<Point> point = std::make_shared<Point>(Pos->x, Pos->y, Pos->z);

		this->addPoint(point);
	}
	/**
	 * @brief add point to point group
	 * 
	 * @param pos Vectro3f of point position
	 */
	void addPoint(Vector3f pos)
	{
		this->addPoint(std::make_shared<Point>(pos));
	}

/**
 * @brief adds point with specifed xyz coridantes
 * 
 * @param x postion in x axis
 * @param y postion in y axis 
 * @param z postion z axis
 */
	void addPoint(float x, float y, float z)
	{
		this->addPoint(std::make_shared<Point>(x, y, z));
	}
	/**
	 * @brief add point to point group with specided corsinates in intlizer float list
	 * 
	 * @param coordinates intilzer list float with coordiantes
	 */
	void addPoint(std::initializer_list<float> coordinates)
	{
		std::shared_ptr<Point> pt = std::make_shared<Point>(coordinates);
		this->addPoint(pt);
	}
	/**
	 * @brief add multiply  ponints using inlizer list coordianres
	 * 
	 * @param coordinates list of cooridantes list
	 */
	void addPoints(std::initializer_list<std::initializer_list<float> > coordinates)
	{
		for (std::initializer_list<float> coord : coordinates)
		{
			this->addPoint(coord);
		}
	}

/**
 * @brief adds point with specifed color nad scale
 * 
 * @param x postiion in x axis
 * @param y postion in y axis
 * @param z postion in z axis
 * @param r color red val
 * @param g color g value
 * @param b color b  value
 * @param pscale scale of point
 */
	virtual void addPoint(float x, float y, float z, float r, float g, float b, float pscale=10)
    {
		addPoint(std::make_shared<Point>(x, y, z, r, g, b, pscale));
    }
/**
 * @brief remove all points from list
 * 
 */
	virtual void cleanGeo()
    {

		points.clear();
    }
};

