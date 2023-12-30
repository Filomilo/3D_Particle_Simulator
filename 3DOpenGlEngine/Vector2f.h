/**
 * @file Vector2f.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief a file conitng implemation of class Vectro 2f
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once
#include <ostream>

#include "Float.h"
/**
 * @brief Vector 3f implementing functionality of 2 value float vector on top of Float class
 * 
 */
class Vector2f :
    public Float
{

public:
/**
 * @brief union containing possible way of addressing 2 value of vector
 * 
 */
    union{
        /**
        * @brief a letter acces to second value of vector in xyzw style
         * 
         */
    float y;
    /**
      * @brief a letter acces to second value of vector in rgba style
     * 
     */
    float g;
    };

/**
 * @brief Construct a new Vector 2f object with 2 vlaues
 * 
 * @param x x value of vecotr
 * @param y y value of vector
 */
    Vector2f(float x, float y)
	    : Float(x),
	      y(y)
    {
    }
/**
 * @brief Construct a new Vector 2f object with ddefault all values 0
 * 
 */
    Vector2f()
    {
        y = 0;
    }

/**
 * @brief overloading operator + allowing to add two vector2f to one
 * 
 * @param other 
 * @return Vector2f 
 */
    Vector2f operator+(const Vector2f& other) const {
        return Vector2f(x + other.x, y+other.y);
    }
/**
* @brief overloading operator allowing to subtract vector3f from each other 
 * 
 * @param other 
 * @return Vector2f 
 */
    Vector2f operator-(const Vector2f& other) const {
        return Vector2f(x - other.x, y - other.y);
    }
/**
 * @brief overlaoding operator * allowing to multuply vectro value artythemtcly
 * 
 * @param other 
 * @return Vector2f 
 */
    Vector2f operator*(const Vector2f& other) const {
        return Vector2f(x * other.x, y * other.y);
    }
/**
 * @brief overloading operator / allowing to divide vectors2f members arithmetically
 * 
 * @param other 
 * @return Vector2f 
 */
    Vector2f operator/(const Vector2f& other) const {
        return Vector2f(x / other.x, y / other.y);
    }
    /**
     * @brief overloading operatior / to allwo to divide vector2f members by one flaot value
     * 
     * @param other 
     * @return Vector2f 
     */
    Vector2f operator/(float other) const {
        return Vector2f(x / other, y / other);
    }
/**
 * @brief overlaading operator [] allowing to acces vector members like in array
 * 
 * @param index 
 * @return float& corresponing vlaue in in index
 */
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
/**
 * @brief Get the amount of elements in vector
 * 
 * @return int amount of vector elemts
 */
    int getSize()const override
    {
        return VECTOR2F;
    }

/**
 * @brief operator << allowinrg to print vector using using in brackets
 * 
 * @param os 
 * @param obj 
 * @return std::ostream& 
 */
    friend std::ostream& operator<<(std::ostream& os, const Vector2f& obj)
    {
	    return os<<"[" << obj.x<< ", " << obj.y<<"]";
    }
/**
 * @brief method calcluats length using pythogarm theory
 * 
 * @return float- length of vector
 */
    float length()
    {
       return sqrt(x * x + y * y);
    }
};

