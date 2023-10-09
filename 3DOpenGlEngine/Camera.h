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
    const float cameraSpeedFactor = 100;

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
        set_aspect((float)width / (float)height);
    }

    void applyZoom(int scroll_movement)
    {
        this->move(Vector3f(0, 0.1* scroll_movement, 0));
        //std::cout << this->get_position() << std::endl;
    }



    void applyMouseMovement(Vector2f movement)
    {
	  
		//	this->rotateY(movement.x * this->cameraSpeedFactor);
            //this->rotateX(movement.y * this->cameraSpeedFactor);
            //this->rotate(movement.y * -1.0 * this->cameraSpeedFactor, getFullPositon());
          //  std::cout << "vector: " << getFullPositon() << std::endl;
            Vector3f Pos= getFullPositon() - get_position();
            Vector3f target =get_position();
            std::cout << "Pos: " << Pos << std::endl;

            float angle = atan2(Pos.z , Pos.x);// *(180 / 3.14);
            float rotXfactor = sin(angle);// sin(rotationQuat.y / 4);
            float rotZfactor = -cos(angle);
           // this->rotateY(movement.x  * this->cameraSpeedFactor );
          //  this->rotateX(movement.y  * this->cameraSpeedFactor  * rotXfactor);
          //  this->rotateZ(movement.y * this->cameraSpeedFactor  * rotXfactor);
    	//	this->rotate(-movement.y * this->cameraSpeedFactor, Vector3f(glm::cross(glm::vec3(0, 1, 0),glm::vec3(Pos.x,Pos.y,Pos.z))));
          //  std::cout << "rotXfactor: " << rotXfactor << "\t" << "rotZfactor: " << rotZfactor << std::endl;


            glm::mat4 yawRotation = glm::rotate(glm::mat4(1.0f), glm::radians(movement.x) * cameraSpeedFactor, glm::vec3(0, 1, 0));
            glm::mat4 pitchRotation = glm::rotate(glm::mat4(1.0f), glm::radians(movement.y*cameraSpeedFactor), glm::cross(glm::vec3(0, 1, 0), Pos.glm()));
            originPointTransformation = yawRotation* pitchRotation* originPointTransformation;


    }
};

