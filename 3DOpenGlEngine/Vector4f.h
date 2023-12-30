/**
 * @file Vector4f.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief A file containing class Vector4f
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once
#include "Vector3f.h"
/**
 * @brief Vector 4f implementing functionality of 4 value float vector on top of 3 value float vector
 * 
 */
class Vector4f :
    public Vector3f
{
public:


/**
 * @brief union containing possible way of addressing 4 value of vector
 * 
 */
	union 
	{
        /**
         * @brief a letter acces to forth value of vector in xyzw style
         * 
         */
		float w;
        /**
         * @brief a letter acces to forth value of vector in rgba style
         * 
         */
		float a;
	};

/**
 * @brief Construct a new Vector 4f object with all 4 values
 * 
 * @param x first value of vector
 * @param y second value of vector
 * @param z thrid value of vector
 * @param w forth value of vector
 */
	Vector4f(float x, float y, float z, float w)
		: Vector3f(x, y, z),
		  w(w)
	{
	}
    /**
     * @brief Construct a new Vector 4f object with default all 0 zero values
     * 
     */
    Vector4f()
	{
        w = 0;
	}


/**
 * @brief overloading operator + allowing to add two vector4f to one
 * 
 * @param other 
 * @return Vector4f 
 */
    Vector4f operator+(const Vector4f& other) const {
        return Vector4f(x + other.x, y + other.y, z + other.z, w + other.w);
    }
/**
 * @brief overloading operator allowing to subtract vector4f from each other 
 * 
 * @param other 
 * @return Vector4f 
 */
    Vector4f operator-(const Vector4f& other) const {
        return Vector4f(x - other.x, y - other.y, z - other.z, w- other.w);
    }
/**
 * @brief overlaoding operator * allowing to multuply vectro value artythemtcly
 * 
 * @param other 
 * @return Vector4f 
 */
    Vector4f operator*(const Vector4f& other) const {
        return Vector4f(x * other.x, y * other.y, z * other.z, w * other.w);
    }
/**
 * @brief overloading operator / allowing to divide vectors4f members arithmetically
 * 
 * @param other 
 * @return Vector4f 
 */
    Vector4f operator/(const Vector4f& other) const {
        return Vector4f(x / other.x, y / other.y, z / other.z, w / other.w);
    }
/**
 * @brief overlaading operator [] allowing to acces vector members like in array
 * 
 * @param index 
 * @return float& 
 */
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
/**
 * @brief Get the amount of vector members/type of vector
 * 
 * @return int 
 */
    int getSize()const override
    {
        return VECTOR4F;
    }
/**
 * @brief overloading operator << aloowing to print vector using cout
 * 
 * @param os 
 * @param obj 
 * @return std::ostream& 
 */
    friend std::ostream& operator<<(std::ostream& os, const Vector4f& obj)
    {
        return os << "[" << obj.x << ", " << obj.y << ", " << obj.z << ", " << obj.w << "]";
    }

};

