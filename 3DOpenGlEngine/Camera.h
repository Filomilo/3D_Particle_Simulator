/**
 * @file Camera.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file containg camera class
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include <complex>

#include "Mouse.h"
#include "Transformable.h"
/**
 * @brief camerar clas fro hadnlign amrea postion movment nad projection
 * 
 */
class Camera :
    public Transformable
{
private:
/**
 * @brief  projection matrix used in opengl
 * 
 */
    glm::mat4 projection = glm::mat4(1);
/**
 * @brief fovc apramter
 * 
 */
    float fov;
    /**
     * @brief aspect paramter
     * 
     */
    float aspect;
    /**
     * @brief near plane clipping 
     * 
     */
    float nearPlane;
    /**
     * @brief far plane clippign
     * 
     */
    float farPlane;
    /**
     * @brief speed of camera movment
     * 
     */
    const float cameraSpeedFactor =0.2;
/**
 * @brief initlize camera object
 * 
 */
    void iniit()
    {
        projection = glm::perspective(glm ::radians( this->fov), this->aspect, this->nearPlane, this->farPlane);
    }
/**
 * @brief Get the Look At Matrix object
 * 
 * @return glm::mat4 
 */
    glm::mat4 getLookAtMatrix()
    {
        return glm::lookAt(glm::vec3(this->getFullPositon().x, this->getFullPositon().y, this->getFullPositon().z), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    }


public:
/**
 * @brief Construct a new Camera object
 * 
 * @param fov 
 * @param aspect 
 * @param near_plane 
 * @param far_plane 
 */
    Camera(float fov, float aspect, float near_plane, float far_plane)
	    : fov(fov),
	      aspect(aspect),
	      nearPlane(near_plane),
	      farPlane(far_plane),
         Transformable()
    {
        iniit();
    }
/**
 * @brief Get the fov object
 * 
 * @return float 
 */
    float get_fov() const
    {
	    return fov;
    }
/**
 * @brief Set the fov object
 * 
 * @param fov 
 */
    void set_fov(float fov)
    {
	    this->fov = fov;
        iniit();
    }
/**
 * @brief Get the aspect object
 * 
 * @return float 
 */
    float get_aspect() const
    {
	    return aspect;
    }
/**
 * @brief Set the aspect object
 * 
 * @param aspect 
 */
    void set_aspect(float aspect)
    {
	    this->aspect = aspect;
        iniit();
    }
/**
 * @brief Get the near plane object
 * 
 * @return float 
 */
    float get_near_plane() const
    {
	    return nearPlane;
    }
/**
 * @brief Set the near plane object
 * 
 * @param near_plane 
 */
    void set_near_plane(float near_plane)
    {
	    nearPlane = near_plane;
        iniit();
    }
/**
 * @brief Get the far plane object
 * 
 * @return float 
 */
    float get_far_plane() const
    {
	    return farPlane;
    }
/**
 * @brief Set the far plane object
 * 
 * @param far_plane 
 */
    void set_far_plane(float far_plane)
    {
	    farPlane = far_plane;
        iniit();
    }


/**
 * @brief Get the Camera Matrix object
 * 
 * @return glm::mat4 
 */
    glm::mat4 getCameraMatrix()
    {
        return  projection*this->getLookAtMatrix() ;
    }
/**
 * @brief Set the aspect object
 * 
 * @param width 
 * @param height 
 */
    void set_aspect(int width, int height)
    {
        if(width>0 && height>0)
        set_aspect((float)width / (float)height);
    }
/**
 * @brief aplpl zoom change whie scrolling
 * 
 * @param value 
 */
    void applyZoom(float value)
    {
     //   this->moveIndendent(getFullPositon()*value);
      //  std::cout << this->get_position() << std::endl;
        Vector3f scaling = Vector3f(1, 1, 1) ;
        if (value != 0) {
     if(value>0)
            scaling = Vector3f(0.9, 0.9, 0.0) ;
     else
         scaling = Vector3f(1.1, 1.1, 1.1) ;
            scale(scaling);
        }
       // move(pos);
        //std::cout << getFullPositon() << ", " << get_position() <<", "<<value<< std::endl;
    }


/**
 * @brief applies movment of mouse to camera
 * 
 * @param movement 
 */
    void applyMouseMovement(Vector2f movement)
    {
	  

            Vector3f Pos= getFullPositon() - get_position();


            glm::mat4 yawRotation = glm::rotate(glm::mat4(1.0f), glm::radians(movement.x) * cameraSpeedFactor, glm::vec3(0, 1, 0));
            glm::mat4 pitchRotation = glm::rotate(glm::mat4(1.0f), glm::radians(movement.y*cameraSpeedFactor), glm::cross(glm::vec3(0, 1, 0), Pos.glm()));
            originPointTransformation = yawRotation* pitchRotation* originPointTransformation;


    }
};

