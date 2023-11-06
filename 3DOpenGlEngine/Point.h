#pragma once
#include <iostream>

#include "Object.h"
#include "Vector3f.h"

class Point :
    public Object
{

    public:

    Point(float x=0, float y=0, float z=0) : Object()
    {
        std::shared_ptr<Vector3f> pos= std::make_shared<Vector3f>(x, y, z);
        this->setAttribute("P",pos);
    }

    Point(Vector3f pos) : Object()
    {
        this->setAttribute("P", std::make_shared<Vector3f>(pos));
    }

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

    void setColor(float r,float g, float b)
    {
       std::shared_ptr< Vector3f> cd = std::make_shared<Vector3f>(r,g,b);
        this->setAttribute("Cd", cd);
    }

    void setPscale(float size)
    {
        std::shared_ptr<Float> pscale = std::make_shared<Float>(size);
        this->setAttribute("pscale", pscale);
    }

    void setVelocity(float x, float y, float z)
    {
       std::shared_ptr< Vector3f> V = std::make_shared<Vector3f>(x,y,z);
        this->setAttribute("V", V);
    }

    void setMass(float mass)
    {
        std::shared_ptr<Float> Mass = std::make_shared<Float>(mass);
        this->setAttribute("mass", Mass);
    }

    void setBounce(float bounce)
    {
        std::shared_ptr<Float> Bounce = std::make_shared<Float>(bounce);
        this->setAttribute("bounce", Bounce);
    }

    void setLife(float life)
    {
        std::shared_ptr<Float> Life = std::make_shared<Float>(life);
        this->setAttribute("life", Life);
    }
    void setAge(float age)
    {
        std::shared_ptr<Float> Age = std::make_shared<Float>(age);
        this->setAttribute("age", Age);
    }


    void increaseAge(float amount)
    {
        std::shared_ptr<Float> Age = std::dynamic_pointer_cast<Float>(getAttribute("age"));
        this->setAge(Age->x + amount);
    }



    Point(float x, float y, float z, float r, float g, float b, float size=1):Point(x,y,z)
    {
        setColor(r, g, b);
        setPscale(size);
      
    }

    ~Point()
    {

    }
};

