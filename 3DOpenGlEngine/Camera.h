#pragma once
#include "Transformable.h"
class Camera :
    public Transformable
{
private:

    glm::mat4 projection = glm::mat4(1);

    float fov;
    float aspect;
    float nearPlane;
    float farPlane;

    void iniit()
    {
        projection = glm::perspective(glm ::radians( this->fov), this->aspect, this->nearPlane, this->farPlane);
    }

public:
    Camera(float fov, float aspect, float near_plane, float far_plane)
	    : fov(fov),
	      aspect(aspect),
	      nearPlane(near_plane),
	      farPlane(far_plane)
    {
        iniit();
    }

    float get_fov() const
    {
	    return fov;
    }

    void set_fov(float fov)
    {
	    this->fov = fov;
        iniit();
    }

    float get_aspect() const
    {
	    return aspect;
    }

    void set_aspect(float aspect)
    {
	    this->aspect = aspect;
        iniit();
    }

    float get_near_plane() const
    {
	    return nearPlane;
    }

    void set_near_plane(float near_plane)
    {
	    nearPlane = near_plane;
        iniit();
    }

    float get_far_plane() const
    {
	    return farPlane;
    }

    void set_far_plane(float far_plane)
    {
	    farPlane = far_plane;
        iniit();
    }



    glm::mat4 getCameraMatrix()
    {
        return this->getTransformationMatrix() * this->projection;
    }
};

