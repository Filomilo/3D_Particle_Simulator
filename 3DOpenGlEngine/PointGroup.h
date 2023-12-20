#pragma once
#include "GlObject.h"
#include "Point.h"
class PointGroup :
    public GlObject
{
protected:
    std::vector<std::shared_ptr<Point>> points;

	std::shared_ptr<Attribute> getVertexAttrib(int num, std::string attrib) override
	{
		std::shared_ptr<Point> pt = this->points.at(num);
		if (!pt->isThereAttrib(attrib)) {
			return pt->getAttribute(attrib);
		}
		return pt->getAttribute(attrib);
	}

	int getVerteciesAmount() override
	{
		return points.size();
	}


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

	GLfloat* getVertexBuffer() override
	{
		
		return  getVertexBufferForMat(this->mat);
	}
	void glDrawCall() override
	{
		glDrawArrays(GL_POINTS, 0, getVerteciesAmount());
	}

public:
    PointGroup(): GlObject()
    {}


	void addPoint(std::shared_ptr<Point> x)
	{
		this->points.push_back(x);
	}
	void addPoint(Point pt)
	{
		 std::shared_ptr<Vector3f> Pos = std::dynamic_pointer_cast <Vector3f>(pt.getAttribute("P"));
		std::shared_ptr<Point> point = std::make_shared<Point>(Pos->x, Pos->y, Pos->z);

		this->addPoint(point);
	}
	void addPoint(Vector3f pos)
	{
		this->addPoint(std::make_shared<Point>(pos));
	}


	void addPoint(float x, float y, float z)
	{
		this->addPoint(std::make_shared<Point>(x, y, z));
	}
	void addPoint(std::initializer_list<float> coordinates)
	{
		std::shared_ptr<Point> pt = std::make_shared<Point>(coordinates);
		this->addPoint(pt);
	}
	void addPoints(std::initializer_list<std::initializer_list<float> > coordinates)
	{
		for (std::initializer_list<float> coord : coordinates)
		{
			this->addPoint(coord);
		}
	}


	virtual void addPoint(float x, float y, float z, float r, float g, float b, float pscale=10)
    {
		addPoint(std::make_shared<Point>(x, y, z, r, g, b, pscale));
    }

	virtual void cleanGeo()
    {

		points.clear();
    }
};

