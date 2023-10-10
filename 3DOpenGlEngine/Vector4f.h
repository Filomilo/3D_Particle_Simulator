#pragma once
#include "Vector3f.h"
class Vector4f :
    public Vector3f
{
public:

	union 
	{
		float w;
		float a;
	};


	Vector4f(float x, float y, float z, float w)
		: Vector3f(x, y, z),
		  w(w)
	{
	}
    Vector4f()
	{
        w = 0;
	}



    Vector4f operator+(const Vector4f& other) const {
        return Vector4f(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    Vector4f operator-(const Vector4f& other) const {
        return Vector4f(x - other.x, y - other.y, z - other.z, w- other.w);
    }

    Vector4f operator*(const Vector4f& other) const {
        return Vector4f(x * other.x, y * other.y, z * other.z, w * other.w);
    }

    Vector4f operator/(const Vector4f& other) const {
        return Vector4f(x / other.x, y / other.y, z / other.z, w / other.w);
    }

    float& operator[](int index)  {
        if (index < 0 || index>3)
        {
            throw  std::out_of_range("Vector4f has only indecies betwee 0 - 3");
        }

        switch (index)
        {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        }


    }

    int getSize()const override
    {
        return VECTOR4F;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector4f& obj)
    {
        return os << "[" << obj.x << ", " << obj.y << ", " << obj.z << ", " << obj.w << "]";
    }

};

