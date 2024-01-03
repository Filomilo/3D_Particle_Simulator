/**
 * @file Face.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file coanitng face class
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include <vector>

#include "Object.h"
/**
 * @brief class for annling data about specifc face of polygonal objeect
 * 
 */
class Face :
    public Object
{
/**
 * @brief indecies of verteies mkaing out this face
 * 
 */
    std::vector<unsigned int> vertexIndecies;

public:
/**
 * @brief Construct a new Face object
 * 
 * @param vertexIndecies 
 */
    explicit Face(std::initializer_list<unsigned int> vertexIndecies) : Object()
    {
        for (unsigned int index : vertexIndecies) {
            this->vertexIndecies.push_back(index);
        }
    }
/**
 * @brief Construct a new Face object
 * 
 */
    Face() : Object()
    {
	    
    }

/**
 * @brief Get the vertex indecies object
 * 
 * @return std::vector<unsigned> 
 */
    std::vector<unsigned> get_vertex_indecies() const
    {
	    return vertexIndecies;
    }
/**
 * @brief Set the vertex indecies object
 * 
 * @param vertex_indecies 
 */
    void set_vertex_indecies(const std::vector<unsigned>& vertex_indecies)
    {
        vertexIndecies = vertex_indecies;
    }
/**
 * @brief add vetex index to face
 * 
 * @param index 
 */
    void addPointINdex(unsigned int index)
    {
        this->vertexIndecies.push_back(index);
    }


    ~Face()
    {

    }
};

