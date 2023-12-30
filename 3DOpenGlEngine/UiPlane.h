/**
 * @file UiPlane.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file implementing Ui plane class
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "Polygonal.h"
#include "ShaderLib.h"
/**
 * @brief UI plane showing on screen
 * 
 * class base for ui method showing on screen always in the same 2d plane on screen
 * 
 */
class UiPlane :
    public Polygonal
{
public:
	UiPlane(void * empty){}
	/**
	 * @brief Construct a new Ui Plane object
	 * 
	 * base consturct seetting basseic plane add ui Shader
	 * 
	 */
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
		setMat(std::make_shared<Material>(ShaderLib::UiShader));
		//set_render_mode(GL_LINES);
		init();
		
    }

	void setTex( std::shared_ptr<Texture> tex)
    {
		this->mat->addTex("color", tex);
    }

  
};

