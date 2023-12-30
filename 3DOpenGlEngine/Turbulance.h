/**
 * @file Turbulance.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file coanting Turbulance force implemtantion
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "Force.h"
#include "Noise.h"
/**
 * @brief Turbulance class force
 * 
 * class implements affect method allwing to add turubulent veloctiy in simualtion
 * 
 */
class Turbulance :
    public Force
{
private:
/**
 * @brief scale factor
 * 
 * scale factor multiply force to add in simulation
 * 
 */
   std::shared_ptr<Float> scale=std::make_shared<Float>( 0.001);
   /**
    * @brief seed for random noise
    * 
    */
    int seed = 0;

public:
/**
 * @brief affect method appliyng noise velocity
 * 
 * it gets noise from noise class and get velcoty based on point position 
 * 
 * @param pt point affected in siumaltion
 * @param timeVal time facot form prevois run
 */
    void affect(std::shared_ptr<Point> pt, float timeVal) override
    {
       std::shared_ptr< Vector3f> pos =std::dynamic_pointer_cast <Vector3f>( pt->getAttribute("P"));
       std::shared_ptr< Vector3f> vel =  std::dynamic_pointer_cast<Vector3f>( pt->getAttribute("V"));
        Vector3f turbulance = Noise::getNoise(*pos, seed) * scale->x;
        *vel = *vel + turbulance;


    }

    /**
     * @brief Get the Parameter Group object
     * 
     * created ui paramter group with ponter to scale factor of turbulance force
     * @return std::shared_ptr<UiParameterGroup> 
     */
    std::shared_ptr<UiParameterGroup> getParameterGroup() override
    {
        std::shared_ptr<UiParameterGroup> ui_parameter_group = std::make_shared<UiParameterGroup>("Turbulance");
        ui_parameter_group->addParameter(std::make_shared<UiParameter> ("scale", this->scale, 0.001));
        return ui_parameter_group;
    }



};

