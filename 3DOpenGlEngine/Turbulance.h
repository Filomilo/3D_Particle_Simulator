#pragma once
#include "Force.h"
#include "Noise.h"

class Turbulance :
    public Force
{
private:
    float scale=0.001;
    int seed = 0;

public:
    void affect(Point* pt, float timeVal) override
    {
        Vector3f* pos =(Vector3f*) pt->getAttribute("P");
        Vector3f* vel = (Vector3f*) pt->getAttribute("V");
        Vector3f turbulance = Noise::getNoise(*pos, seed) *scale;
        *vel = *vel + turbulance;


    }




};

