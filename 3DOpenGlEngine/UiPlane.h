#pragma once
#include "Polygonal.h"
#include "ShaderLib.h"
class UiPlane :
    public Polygonal
{
public:
    UiPlane()
    {
		this->addPoint(-1,-1,0);
		this->addPoint(1, -1, 0);
		this->addPoint(1, 1, 0);
		this->addPoint(-1, 1, 0);
		this->addVertex(0, { 0.000000, 1.000000 ,0.000000 }, { 0.0, 0.000000 });
		this->addVertex(1, { 0.000000, 1.000000, 0.000000 }, { 1.0 ,0.0 });
		this->addVertex(2, { 0.000000, 1.000000 ,0.000000 }, { 1.0, 1.0, });
		this->addVertex(3, { 0.000000, 1.000000, 0.000000 }, { 0.0, 1.0 });

		this->addFace({ 0,1,2,3 });
		setMat(new Material(ShaderLib::UiShader));
		//set_render_mode(GL_LINES);
		init();
		
    }

	void setTex(Texture* tex)
    {
		this->mat->addTex("color", tex);
    }

  
};

