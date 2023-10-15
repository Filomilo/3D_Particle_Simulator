#pragma once
#include "GlObject.h"
#include "Point.h"
class PointGroup :
    public GlObject
{
protected:
    std::vector<Point*> points;

	Attribute* getVertexAttrib(int num, std::string attrib) override
	{
		Point* pt = this->points.at(num);
		if (!pt->isThereAttrib(attrib)) {
			return pt->getAttribute(attrib);
		}
		return pt->getAttribute(attrib);
	}

	int getVerteciesAmount() override
	{
		return points.size();
	}

	float* getVertexBuffer() override
	{
		float* arrayVbo = new float[this->getVerteciesAmount() * this->getVertexSize()];

		std::map<std::string, Attribute::Types> attributesMap = mat->getAttributeMap();
		std::list<std::string> attributeList = mat->getAttributeList();
		int index = 0;
		int vertIndex = 0;
		for (Point* vertex : this->points)
		{
			for (std::string attribName : attributeList)
			{
				Attribute::Types attribType = attributesMap.find(attribName)->second;
				Vector4f* attribVal = (Vector4f*)this->getVertexAttrib(vertIndex, attribName);

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
	void glDrawCall() override
	{
		glDrawArrays(GL_POINTS, 0, getVerteciesAmount());
	}

public:
    PointGroup(): GlObject()
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
	void addPoint(Vector3f pos)
	{
		this->addPoint(new Point(pos));
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


	void addPoint(float x, float y, float z, float r, float g, float b)
    {
		addPoint(new Point(x, y, z, r, g, b));
    }


};

