#pragma once
#include "glObject.h"
class PointGroupObject :
    public glObject
{
protected:
	std::vector<Point*> points;



public:

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
	void addPoint(Vector3f pos)
	{
		this->addPoint(new Point(pos));
	}


	virtual  int getVerteciesAmount() override
	{
		return points.size();
	}
	virtual Attribute* getVertexAttrib(int num, std::string attrib) override=0;
	virtual float* getVertexBuffer() override = 0;
	virtual void iniit() override = 0;
};

