/**
 * @file Vertex.h
 * @author your name (fborowiec@wp.pl)
 * @brief file containing Vertex class
 * @version 0.1
 * @date 2023-12-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#pragma once
#include "Object.h"
#include "Vector3f.h"
class Vertex :
    public Object
{
public:
/**
 * @brief index number of corresponding point in main object
 * 
 */
    unsigned int pointIndex;

/**
 * @brief Construct a new Vertex object that include point index in main object
 * 
 * @param point_index index of point in main object 
 */
    explicit Vertex(unsigned point_index)
	    : pointIndex(point_index)
    {
    }


/**
 * @brief Construct a new Vertex object including index of point and normal vector
 * 
 * @param point_index index of point in main object 
 * @param normals normal vector of vertex
 */
    Vertex(int pointNUm, Vector3f normals) : Vertex(pointNUm)
    {
        this->setAttribute("N", std::make_shared<Vector3f>(normals.x, normals.y, normals.z));
    }
/**
 * @brief Construct a new Vertex object including index of point and normal vector
 * 
 * @param point_index index of point in main object 
 * @param normals normal vector of vertex
*/
    Vertex(int pointNUm,std::shared_ptr< Vector3f> normals) : Vertex(pointNUm)
    {
        this->setAttribute("N", normals);
    }

/**
 * Vertex constructor that iclunde corresponfing index that includes normal vector and uv coordinates
*/
    Vertex(int pointNUm,std::shared_ptr< Vector3f> normals,std::shared_ptr< Vector3f> uv) : Vertex(pointNUm, normals)
    {
        this->setAttribute("Uv", normals);
    }
/**
 * Vertex constuctor including point index and uvs as not shared pointers
*/
    Vertex(int pointNUm, Vector3f normals, Vector2f Uvs) : Vertex(pointNUm, normals)
    {
        this->setAttribute("Uv", std::make_shared<Vector2f>(Uvs.x, Uvs.y));

    }

};

