#pragma once
#include "Vector2f.h"
class Vector3f :
    public Vector2f
{
public:
    union {
        float z;
        float b;
    };


    Vector3f(float x=0, float y=0, float z=0)
	    : Vector2f(x, y),
	      z(z)
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
};

