#pragma once
#include <ostream>
#include <stdexcept>

#include "Attribute.h"
class Float :
    public Attribute
{

  
public:
    union {
        float x;
        float r;
    };

     Float(float x)
	    : x(x)
    {
    }


     Float ()
     {
         x = 0;
     }
    Float operator+(const Float& other) const {
        return Float(x + other.x);
    }

    Float operator-(const Float& other) const {
        return Float(x - other.x);
    }

	Float operator*(const Float& other) const {
        return Float(x * other.x);
    }

    Float operator/(const Float& other) const {
        return Float(x / other.x);
    }

    float& operator[](int index)  {
       if(index<0 || index>0)
       {
           throw  std::out_of_range("Float has only index 0");
       }

       return x;

    }
    Float operator-=(const Float& other) const {
        return Float(x - other.x);
    }
    

    int getSize()const override
	{
        return FLOAT;
	}

    friend std::ostream& operator<<(std::ostream& os, const Float& obj)
    {
        os << "[ " << obj.x << " ]";
        return os;

    }
};

