// 3DOpenGlEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <glad/glad.h>

#include "Cube.h"
#include "PhongMat.h"
#include "PointLight.h"
#include "ShaderProgram.h"
#include "_3DEngine.h"

void otherTEst()
{
    _3DEngine* engine = _3DEngine::getInstance();
    engine->iniit(800, 600);
    ShaderProgram shader = ShaderProgram("simpleVertexShader.vert", "phongFragmentShader.frag");
}



void cubeTest()
{
    try {
        _3DEngine* engine = _3DEngine::getInstance();
        engine->iniit(800, 600);


       // ShaderProgram* shader = new ShaderProgram("phongVertexShader.vert", "phongFragmentShader.frag");
       
       // shader->addAttribute("Uv", Attribute::VECTOR2F);
        ShaderProgram* shader = ShaderLib::phongShader;
        Material* basicMat = new Material(shader);
        Texture* tex = new Texture("Assets/cube_initialShadingGroup_BaseColor.bmp", 2048, 2048, 8);
        basicMat->addTex("colorTexture", tex);
        PhongMat* cubeMat = new PhongMat;
        cubeMat->set_color_tex("Assets/cube_initialShadingGroup_BaseColor.bmp", 2048, 2048, 24);
        cubeMat->set_normal_tex("Assets/cube_initialShadingGroup_Normal.bmp", 2048, 2048, 24);
       cubeMat->set_rough_tex("Assets/cube_initialShadingGroup_Roughness.bmp", 2048, 2048, 8, GL_RED);




        PhongMat* basicMatplane = new PhongMat;
        basicMatplane->set_color_tex("Assets/plane_initialShadingGroup_BaseColor.png", 2048, 2048, 24);
        basicMatplane->set_normal_tex("Assets/plane_initialShadingGroup_Normal.png", 2048, 2048, 24);
        basicMatplane->set_rough_tex("Assets/plane_initialShadingGroup_Roughness.png", 2048, 2048, 8, GL_RED);
        Cube* cube = new Cube(5);
        cube->setMat(cubeMat);
        cube->initilizePolygonal();
       cube->moveY(2.501);

        engine->addShader(shader);

       
        engine->addRenderable(cube);
        try {
            PolyGrid* polygrid = new PolyGrid(20, 20, 2, 2);
            polygrid->setMat(basicMatplane);
            polygrid->initilizePolygonal();
            engine->addRenderable(polygrid);

        }
        catch(std::exception ex)
        {
            std::cerr << "Error creating groundPlane: " << ex.what();
        }



        PointLight* pointLight = new PointLight;
        pointLight->move(Vector3f(0, 5, 5));
        Light::setAmbientColor(Vector3f(0.8, 0.8, 1));
        Light::setAmbientIntensity(0.4);
        engine->addRenderable(pointLight);


      //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
       // engine->addRenderable(rectangle);
       engine->start();
    }
    catch (std::exception e)
    {
        std::cerr <<"Error: "<< e.what();
    }
}

int main()
{
    cubeTest();
	//Test();
    return 0;
}