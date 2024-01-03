/**
 * @file Float.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file coanting FLaot attribute class
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include <ostream>
#include <stdexcept>

#include "Attribute.h"
/**
 * @brief Float cals attribute
 * 
 */
class Float :
    public Attribute
{

  
public:
/**
 * @brief union conaintg possiblee wayas to adres value
 * 
 */
    union {
        float x;
        float r;
    };
/**
 * @brief Construct a new Float object
 * 
 * @param x 
 */
     Float(float x)
	    : x(x)
    {
    }

/**
 * @brief Construct a new Float object
 * 
 */
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

