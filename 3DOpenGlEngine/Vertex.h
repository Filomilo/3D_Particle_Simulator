#pragma once
#include "Object.h"
#include "Vector3f.h"
class Vertex :
    public Object
{
public:
    unsigned int pointIndex;


    explicit Vertex(unsigned point_index)
	    : pointIndex(point_index)
    {
    }



    Vertex(int pointNUm, Vector3f normals) : Vertex(pointNUm)
    {
        this->setAttribute("N", new Vector3f(normals.x, normals.y, normals.z));
    }

    Vertex(int pointNUm, Vector3f* normals) : Vertex(pointNUm)
    {
        this->setAttribute("N", normals);
    }

    Vertex(int pointNUm, Vector3f* normals, Vector3f* uv) : Vertex(pointNUm, normals)
    {
        this->setAttribute("Uv", normals);
    }

    Vertex(int pointNUm, Vector3f normals, Vector2f Uvs) : Vertex(pointNUm, normals)
    {
        this->setAttribute("Uv", new Vector2f(Uvs.x, Uvs.y));
    }

};

