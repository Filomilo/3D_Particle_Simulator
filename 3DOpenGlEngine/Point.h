#pragma once
#include "Object.h"
#include "Vector3f.h"

class Point :
    public Object
{

    public:

    Point(float x=0, float y=0, float z=0) : Object()
    {
        Vector3f* pos= new Vector3f(x, y, z);
        this->setAttribute("P",pos);
    }

    Point(Vector3f pos) : Object()
    {
        this->setAttribute("P", new Vector3f(pos));
    }

     Point(std::initializer_list<float> initializers): Object()
    {
        Vector3f* pos=new Vector3f;
        int i = 0;
	    for (float posVal: initializers)
	    {
            (*pos)[i++] = posVal;
	    }
        this->setAttribute("P", pos);
    }
};

