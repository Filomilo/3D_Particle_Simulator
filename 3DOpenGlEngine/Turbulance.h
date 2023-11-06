#pragma once
#include "Force.h"
#include "Noise.h"

class Turbulance :
    public Force
{
private:
   std::shared_ptr<Float> scale=std::make_shared<Float>( 0.001);
    int seed = 0;

public:
    void affect(std::shared_ptr<Point> pt, float timeVal) override
    {
       std::shared_ptr< Vector3f> pos =std::dynamic_pointer_cast <Vector3f>( pt->getAttribute("P"));
       std::shared_ptr< Vector3f> vel =  std::dynamic_pointer_cast<Vector3f>( pt->getAttribute("V"));
        Vector3f turbulance = Noise::getNoise(*pos, seed) * scale->x;
        *vel = *vel + turbulance;


    }
    std::shared_ptr<UiParameterGroup> getParameterGroup() override
    {
        std::shared_ptr<UiParameterGroup> ui_parameter_group = std::make_shared<UiParameterGroup>("Turbulance");
        ui_parameter_group->addParameter(std::make_shared<UiParameter> ("scale", this->scale, 0.001));
        return ui_parameter_group;
    }



};

