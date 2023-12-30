/**
 * @file PointGroupObject.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file conating poitnGroupObject class
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "glObject.h"
/**
 * @brief class conating points of opengl
 * 
 * class for magingn and redneirgin simple point group in opengl
 * 
 */
class PointGroupObject :
    public glObject
{
protected:
/**
 * @brief list of point in the object
 * 
 */
	std::vector<Point*> points;



public:
/**
 * @brief Construct a new Point Group Object object
 * 
 * basic constructor that setsrender mode to gl points
 * 
 */
	PointGroupObject()
	{
		renderMode = GL_POINTS;
	}
/**
 * @brief add points to point group object 
 * 
 * @param x poitner to Point to be added
 */
	void addPoint(Point* x)
	{
			this->points.push_back(x);
	}
	/**
	 * @brief add point to group
	 * 
	 * @param pt point data
	 */
	void addPoint(Point pt)
	{
		Vector3f* Pos = (Vector3f*)pt.getAttribute("P");
		Point* point = new Point(Pos->x, Pos->y, Pos->z);

		this->addPoint(point);
	}

/**
 * @brief added point at specifed postion
 * 
 * @param x postion in x axis
 * @param y postion in y axis
 * @param z postion in z axxis
 */
	void addPoint(float x, float y, float z)
	{
		this->addPoint(new Point(x, y, z));
	}
	/**
	 * @brief added point based list corrsinates
	 * 
	 * @param coordinates list of corrsinates
	 */
	void addPoint(std::initializer_list<float> coordinates)
	{
		Point* pt = new Point(coordinates);
		this->addPoint(pt);
	}
	/**
	 * @brief add point based list of list of paramters
	 * 
	 * @param coordinates 
	 */
	void addPoints(std::initializer_list<std::initializer_list<float> > coordinates)
	{
		for (std::initializer_list<float> coord : coordinates)
		{
			this->addPoint(coord);
		}
	}

/**
 * @brief add points based on its postion
 * 
 * @param pos postion of point
 */
	void addPoint(Vector3f pos)
	{
		this->addPoint(new Point(pos));
	}

/**
 * @brief Get the Vertecies Amount object
 * 
 * @return int 
 */
	virtual  int getVerteciesAmount() override
	{
		return points.size();
	}
	/**
	 * @brief Get the Vertex Attrib object
	 * get attribure og point index ands set it there is none
	 * 
	 * @param num 
	 * @param attrib 
	 * @return Attribute* 
	 */
	virtual Attribute* getVertexAttrib(int num, std::string attrib)
	{
		Point* pt = points.at(num);
		if (pt->isThereAttrib(attrib))
			return pt->getAttribute(attrib);
		Attribute* val= new Vector4f;
		pt->setAttribute(attrib, val);
		return val;

	}	
	/**
	 * @brief Get the Vertex Buffer object
	 * 
	 * vrates veretx buffer object for open gl
	 * 
	 * @return float* 
	 */
	virtual float* getVertexBuffer() override
	{
		float* arrayVbo = new float[this->getVerteciesAmount() * this->getVertexSize()];

		std::map<std::string, Attribute::Types> attributesMap = mat->getAttributeMap();
		std::list<std::string> attributeList = mat->getAttributeList();
		int index = 0;
		int vertexIndex = 0;
		for (Point* vertex : this->points)
		{
			for (std::string attribName : attributeList)
			{
				Attribute::Types attribType = attributesMap.find(attribName)->second;
				Vector4f* attribVal = (Vector4f*)this->getVertexAttrib(vertexIndex, attribName);
				for (int i = 0; i < attribType; i++)
				{
					arrayVbo[index++] = (*attribVal)[i];
				//	std::cout << (*attribVal)[i] << ", ";
				}


			}
			//std::cout << std::endl;
			vertexIndex++;
		}

		return  arrayVbo;
	}
	/**
	 * @brief initlizes object for opengl
	 * 
	 */
	virtual void iniit()
	{
		glObject::iniit();
	}
/**
 * @brief adds point with sceifed positon and color
 * 
 * @param x postion in sx axis
 * @param y postion in y axis
 * @param z postion in z axis
 * @param r red color value
 * @param g green color value
 * @param b blue color vlaue
 */
	void addPoint(float x, float y, float z, float r, float g, float b)
	{
		addPoint(new Point( x, y, z, r, g, b));
	}

protected:
/**
 * @brief glrender call to draw point on screen
 * 
 */
	void glRender() override
	{
		glDrawArrays(GL_POINTS, 0, getVerteciesAmount());
	}
};

