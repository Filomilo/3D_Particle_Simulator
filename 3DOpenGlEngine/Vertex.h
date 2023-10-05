#pragma once
#include "Object.h"
class Vertex :
    public Object
{
public:
    unsigned int pointIndex;


    explicit Vertex(unsigned point_index)
	    : pointIndex(point_index)
    {
    }
};

