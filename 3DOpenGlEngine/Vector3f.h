#pragma once

#include <glm/vec3.hpp>

#include "Vector2f.h"
class Vector3f :
    public Vector2f
{
public:
    union {
        float z;
        float b;
    };


    Vector3f(float x, float y, float z)
	    : Vector2f(x, y),
	      z(z)
    {
    }

    Vector3f ()
    {
        z = 0;
    }

    Vector3f(glm::vec3 vec):Vector3f(vec.x,vec.y,vec.z)
    {
	    
    }


    Vector3f operator+(const Vector3f& other) const {
        return Vector3f(x + other.x, y + other.y, z + other.z);
    }

    Vector3f operator-(const Vector3f& other) const {
        return Vector3f(x - other.x, y - other.y,  z - other.z);
    }

    Vector3f operator*(const Vector3f& other) const {
        return Vector3f(x * other.x, y * other.y,  z * other.z);
    }

    Vector3f operator/(const Vector3f& other) const {
        return Vector3f(x / other.x, y / other.y,  z / other.z);
    }

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

    int getSize()const override
    {
        return VECTOR3F;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector3f& obj)
    {
        return os << "[" << obj.x << ", " << obj.y << ", " << obj.z << "]";
    }

    glm::vec3 glm()
    {
        return glm::vec3(x, y, z);
    }
};

