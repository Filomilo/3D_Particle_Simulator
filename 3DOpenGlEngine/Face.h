#pragma once
#include <vector>

#include "Object.h"
class Face :
    public Object
{

    std::vector<unsigned int> vertexIndecies;

public:

    explicit Face(std::initializer_list<unsigned int> vertexIndecies) : Object()
    {
        for (unsigned int index : vertexIndecies) {
            this->vertexIndecies.push_back(index);
        }
    }

    Face() : Object()
    {
	    
    }


    std::vector<unsigned> get_vertex_indecies() const
    {
	    return vertexIndecies;
    }

    void set_vertex_indecies(const std::vector<unsigned>& vertex_indecies)
    {
        vertexIndecies = vertex_indecies;
    }

    void addPointINdex(unsigned int index)
    {
        this->vertexIndecies.push_back(index);
    }


    ~Face()
    {

    }
};

