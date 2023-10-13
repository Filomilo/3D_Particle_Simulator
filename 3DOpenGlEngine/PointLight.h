#pragma once
#include "Cube.h"
#include "Light.h"
#include "ShaderLib.h"









class PointLight :
    public Light,
    public Cube
{
private:
    void setLightPos()
    {
        light_data.lightTypeData[lightNum].position = getFullPositon();
    }

public:
    PointLight(): Light(), Cube(1)
    {
        this->setMat(new Material(ShaderLib::phongShader));
        initilizePolygonal();

        setLightType(POINYLIGHT);
        this->set_render_mode(GL_LINE);
    }

    void move(Vector3f offset) override
    {
        Transformable::move(offset);
        setLightPos();
    }

};

