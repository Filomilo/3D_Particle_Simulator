/**
 * @file Vector3f.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief a file containg implemantion of Vector2f
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <glm/vec3.hpp>
/**
 * @brief Vector 3f implementing functionality of 3 value float vector on top of 2 value float vector
 * 
 */
#include "Vector2f.h"
class Vector3f :
    public Vector2f
{
public:
/**
 * @brief union containing possible way of addressing 3 value of vector
 * 
 */
    union {
               /**
         * @brief a letter acces to third value of vector in xyzw style
         * 
         */
        float z;
               /**
         * @brief a letter acces to third value of vector in rgba style
         * 
         */
        float b;
    };

/**
 * @brief Construct a new Vector 3f with all 3 vectors
 * 
 * @param x 
 * @param y 
 * @param z 
 */
    Vector3f(float x, float y, float z)
	    : Vector2f(x, y),
	      z(z)
    {
    }
/**
 * @brief Construct a new Vector 3f object with all 3 values of 0
 * 
 */
    Vector3f ()
    {
        z = 0;
    }
/**
 * @brief Construct a new Vector 3f object using glm::Vec3 object
 * 
 * @param vec 
 */
    Vector3f(glm::vec3 vec):Vector3f(vec.x,vec.y,vec.z)
    {
	    
    }

/**
 * @brief overloading operator + allowing to add two vector3f to one
 * 
 * @param other 
 * @return Vector3f 
 */
    Vector3f operator+(const Vector3f& other) const {
        return Vector3f(x + other.x, y + other.y, z + other.z);
    }
/**
* @brief overloading operator allowing to subtract vector3f from each other 
 * 
 * @param other 
 * @return Vector3f 
 */
    Vector3f operator-(const Vector3f& other) const {
        return Vector3f(x - other.x, y - other.y,  z - other.z);
    }
/**
 * @brief overlaoding operator * allowing to multuply vectro value artythemtcly
 * 
 * @param other 
 * @return Vector3f 
 */
    Vector3f operator*(const Vector3f& other) const {
        return Vector3f(x * other.x, y * other.y,  z * other.z);
    }
/**
 * @brief overlaoding operator * allowing to multuply vectro value with one float value
 * 
 * @param other 
 * @return Vector3f 
 */
    Vector3f operator*(const float& other) const {
        return Vector3f(x * other, y * other, z * other);
    }
/**
 * @brief overloading operator / allowing to divide vectors3f members arithmetically
 * 
 * @param other 
 * @return Vector3f 
 */
    Vector3f operator/(const Vector3f& other) const {
        return Vector3f(x / other.x, y / other.y,  z / other.z);
    }
/**
 * @brief overlaading operator [] allowing to acces vector members like in array
 * 
 * @param index 
 * @return float& corresponing vlaue in in index
 */
    float& operator[](int index)  {
        if (index < 0 || index>2)
        {
            throw  std::out_of_range("Vector3f has only indecies betwee 0 - 2");
        }

        switch (index)
        {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        }


    }
/**
 * @brief Get the amount of elemnts in vector/ type of vector
 * 
 * @return int 
 */
    int getSize()const override
    {
        return VECTOR3F;
    }
/**
 * @brief operator << allowinrg to print vector using using in brackets
 * 
 * @param os 
 * @param obj 
 * @return std::ostream& 
 */
    friend std::ostream& operator<<(std::ostream& os, const Vector3f& obj)
    {
        return os << "[" << obj.x << ", " << obj.y << ", " << obj.z << "]";
    }
/**
 * @brief function that returns vector value in glm format
 * 
 * @return glm::vec3 
 */
    glm::vec3 glm()
    {
        return glm::vec3(x, y, z);
    }

/**
 * @brief method calcluats length using pythogarm theory
 * 
 * @return float- length of vector
 */
    float length()
    {
        return sqrt(x * x + y * y + z * z);
    }
/**
 * @brief normalisez vector values to achinve length egual to 1
 * 
 * @return Vector3f returns normalized vector
 */
    Vector3f normalize()
    {
        float length = this->length();
        x /=  length;
        y /=  length;
        z /=  length;
        return *this;
    }

};

