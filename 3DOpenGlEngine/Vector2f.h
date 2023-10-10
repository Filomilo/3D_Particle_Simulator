#pragma once
#include <ostream>

#include "Float.h"
class Vector2f :
    public Float
{

public:
    union{
    float y;
    float g;
    };


    Vector2f(float x, float y)
	    : Float(x),
	      y(y)
    {
    }

    Vector2f()
    {
        y = 0;
    }


    Vector2f operator+(const Vector2f& other) const {
        return Vector2f(x + other.x, y+other.y);
    }

    Vector2f operator-(const Vector2f& other) const {
        return Vector2f(x - other.x, y - other.y);
    }

    Vector2f operator*(const Vector2f& other) const {
        return Vector2f(x * other.x, y * other.y);
    }

    Vector2f operator/(const Vector2f& other) const {
        return Vector2f(x / other.x, y / other.y);
    }

    float& operator[](int index)  {
        if (index < 0 || index>1)
        {
            throw  std::out_of_range("Vector2f has only indecies betwee 0 - 1");
        }

        switch (index)
        {
        case 0: return x;
        case 1: return y;

        }


    }

    int getSize()const override
    {
        return VECTOR2F;
    }


    friend std::ostream& operator<<(std::ostream& os, const Vector2f& obj)
    {
	    return os<<"[" << obj.x<< ", " << obj.y<<"]";
    }

    float length()
    {
       return sqrt(x * x + y * y);
    }
};

