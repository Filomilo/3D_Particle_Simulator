#pragma once
#include <complex>

#include "Mouse.h"
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
    const float cameraSpeedFactor =0.2;

    void iniit()
    {
        projection = glm::perspective(glm ::radians( this->fov), this->aspect, this->nearPlane, this->farPlane);
    }

    glm::mat4 getLookAtMatrix()
    {
        return glm::lookAt(glm::vec3(this->getFullPositon().x, this->getFullPositon().y, this->getFullPositon().z), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    }


public:
    Camera(float fov, float aspect, float near_plane, float far_plane)
	    : fov(fov),
	      aspect(aspect),
	      nearPlane(near_plane),
	      farPlane(far_plane),
         Transformable()
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
        return  projection*this->getLookAtMatrix() ;
    }

    void set_aspect(int width, int height)
    {
        if(width>0 && height>0)
        set_aspect((float)width / (float)height);
    }

    void applyZoom(float value)
    {
     //   this->moveIndendent(getFullPositon()*value);
        //std::cout << this->get_position() << std::endl;
        ///TODO: aplication
        ///
     //   Vector3f pos = Vector3f (normalize(getFullPositon().glm())) * value * -0.1;
       // move(pos);
        //std::cout << getFullPositon() << ", " << get_position() <<", "<<value<< std::endl;
    }



    void applyMouseMovement(Vector2f movement)
    {
	  

            Vector3f Pos= getFullPositon() - get_position();


            glm::mat4 yawRotation = glm::rotate(glm::mat4(1.0f), glm::radians(movement.x) * cameraSpeedFactor, glm::vec3(0, 1, 0));
            glm::mat4 pitchRotation = glm::rotate(glm::mat4(1.0f), glm::radians(movement.y*cameraSpeedFactor), glm::cross(glm::vec3(0, 1, 0), Pos.glm()));
            originPointTransformation = yawRotation* pitchRotation* originPointTransformation;


    }
};

