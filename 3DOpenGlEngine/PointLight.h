/**
 * @file PointLight.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file conating point light class
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "Cube.h"
#include "Light.h"
#include "ShaderLib.h"








/**
 * @brief class for mangin point light data in opengl
 * 
 */
class PointLight :
    public Light,
    public Cube
{
private:
/**
 * @brief Set the Light Pos object
 * 
 */
    void setLightPos()
    {
        light_data.lightTypeData[lightNum].position = getFullPositon();
        
    }
    
public:
/**
 * @brief Construct a new Point Light object
 * 
 * cosntruct point light object with type point light and sets int render style lines to be visible in preview
 */
    PointLight(): Light(), Cube(1)
    {
        this->setMat(std::make_shared<Material>(ShaderLib::guideShader));
        init();

        setLightType(POINYLIGHT);
        this->set_render_mode(GL_LINE);
    }
/**
 * @brief overide move method yto move light
 * 
 * @param offset 
 */
    void move(Vector3f offset) override
    {
        Transformable::move(offset);
        setLightPos();
    }
    /**
     * @brief Set the position object
     * 
     * set postion of light
     * 
     * @param position 
     */
    void set_position(Vector3f position) override
    {
        Transformable::set_position(position);
        setLightPos();
    }
};

