/**
 * @file Point.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file conaitng class Point
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once
#include <iostream>

#include "Object.h"
#include "Vector3f.h"
/**
 * @brief class for handling single point
 * 
 * class handles mangain single point form wchi most objet are made out of
 * 
 */
class Point :
    public Object
{

    public:
/**
 * @brief Construct a new Point object
 * 
 * baisc constuctor with xyz cooridante
 * 
 * @param x point positon in x axis
 * @param y position of point in y axis
 * @param z position of point z axis
 */
    Point(float x=0, float y=0, float z=0) : Object()
    {
        std::shared_ptr<Vector3f> pos= std::make_shared<Vector3f>(x, y, z);
        this->setAttribute("P",pos);
    }
/**
 * @brief Construct a new Point object
 * 
 * construcotr that creates point at posiotn specifec by Vector3f 
 * 
 * @param pos position of point in vector3f
 */
    Point(Vector3f pos) : Object()
    {
        this->setAttribute("P", std::make_shared<Vector3f>(pos));
    }
/**
 * @brief Construct a new Point object
 * 
 * bsic constrcuto that creates point in positon specifed by value in inirlizer list
 * 
 * @param initializers 
 */
     Point(std::initializer_list<float> initializers): Object()
    {
       std::shared_ptr<Vector3f> pos=std::make_shared<Vector3f>();
        int i = 0;
	    for (float posVal: initializers)
	    {
            (*pos)[i++] = posVal;
	    }
        this->setAttribute("P", pos);
    }
/**
 * @brief Set the Color object
 * 
 * set color attribute of point to specifed coolor
 * 
 * @param r red color value
 * @param g green color value
 * @param b blue color value
 */
    void setColor(float r,float g, float b)
    {
       std::shared_ptr< Vector3f> cd = std::make_shared<Vector3f>(r,g,b);
        this->setAttribute("Cd", cd);
    }
/**
 * @brief Set the Pscale object
 * 
 * set point scale attriubte of point
 * 
 * @param size size of point
 */
    void setPscale(float size)
    {
        std::shared_ptr<Float> pscale = std::make_shared<Float>(size);
        this->setAttribute("pscale", pscale);
    }
/**
 * @brief Set the Velocity object
 * 
 * set velocity attribute for point 
 * 
 * @param x valocity valeu in x axis
 * @param y velocity in y axis
 * @param z velocity in z axis
 */
    void setVelocity(float x, float y, float z)
    {
       std::shared_ptr< Vector3f> V = std::make_shared<Vector3f>(x,y,z);
        this->setAttribute("V", V);
    }
/**
 * @brief Set the Mass object
 * 
 * set mass of point 
 * 
 * @param mass mass of point
 */
    void setMass(float mass)
    {
        std::shared_ptr<Float> Mass = std::make_shared<Float>(mass);
        this->setAttribute("mass", Mass);
    }
/**
 * @brief Set the Bounce objects
 * 
 * 
 * set bounciness of point
 * 
 * @param bounce bounce value
 */
    void setBounce(float bounce)
    {
        std::shared_ptr<Float> Bounce = std::make_shared<Float>(bounce);
        this->setAttribute("bounce", Bounce);
    }
/**
 * @brief Set the Life object
 * 
 * sets life of point so how maximusm time can it live for 
 * 
 * @param life life of point
 */
    void setLife(float life)
    {
        std::shared_ptr<Float> Life = std::make_shared<Float>(life);
        this->setAttribute("life", Life);
    }
    /**
     * @brief Set the Age object
     * 
     * attrbiute age is define how long point is living for
     * 
     * @param age 
     */
    void setAge(float age)
    {
        std::shared_ptr<Float> Age = std::make_shared<Float>(age);
        this->setAttribute("age", Age);
    }

/**
 * @brief increse age of point
 * 
 * @param amount amount to increase 
 */
    void increaseAge(float amount)
    {
        std::shared_ptr<Float> Age = std::dynamic_pointer_cast<Float>(getAttribute("age"));
        this->setAge(Age->x + amount);
    }


/**
 * @brief Construct a new Point object
 * 
 * create point with postion color and size
 * 
 * @param x postion in x axis
 * @param y postion in y axis
 * @param z poztion in z axis
 * @param r red color value
 * @param g green color value
 * @param b blue color value
 * @param size size of point
 */
    Point(float x, float y, float z, float r, float g, float b, float size=1):Point(x,y,z)
    {
        setColor(r, g, b);
        setPscale(size);
      
    }

    ~Point()
    {

    }
};

