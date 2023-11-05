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
        Vector3f* pos= new Vector3f(x, y, z);
        this->setAttribute("P",pos);
    }

    Point(Vector3f pos) : Object()
    {
        this->setAttribute("P", new Vector3f(pos));
    }

     Point(std::initializer_list<float> initializers): Object()
    {
        Vector3f* pos=new Vector3f;
        int i = 0;
	    for (float posVal: initializers)
	    {
            (*pos)[i++] = posVal;
	    }
        this->setAttribute("P", pos);
    }

    void setColor(float r,float g, float b)
    {
        Vector3f* cd = new Vector3f(r,g,b);
        this->setAttribute("Cd", cd);
    }

    void setPscale(float size)
    {
        Float* pscale = new Float(size);
        this->setAttribute("pscale", pscale);
    }

    void setVelocity(float x, float y, float z)
    {
        Vector3f* V = new Vector3f(x,y,z);
        this->setAttribute("V", V);
    }

    void setMass(float mass)
    {
        Float* Mass = new Float(mass);
        this->setAttribute("mass", Mass);
    }

    void setBounce(float bounce)
    {
        Float* Bounce = new Float(bounce);
        this->setAttribute("bounce", Bounce);
    }

    void setLife(float life)
    {
        Float* Life = new Float(life);
        this->setAttribute("life", Life);
    }
    void setAge(float age)
    {
        Float* Age = new Float(age);
        this->setAttribute("age", Age);
    }


    void increaseAge(float amount)
    {
        Float* Age = (Float*)getAttribute("age");
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

