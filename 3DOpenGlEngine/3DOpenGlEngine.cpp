// 3DOpenGlEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <glad/glad.h>

#include "Cube.h"
#include "ShaderProgram.h"
#include "_3DEngine.h"

void otherTEst()
{
    _3DEngine* engine = _3DEngine::getInstance();
    engine->iniit(800, 600);
    ShaderProgram shader = ShaderProgram("simpleVertexShader.vert", "simpleFragmentShader.frag");
}



void cubeTest()
{
    try {
        _3DEngine* engine = _3DEngine::getInstance();
        engine->iniit(800, 600);


        ShaderProgram* shader = new ShaderProgram("simpleVertexShader.vert", "simpleFragmentShader.frag");
        shader->addAttribute("Uv", Attribute::VECTOR2F);

        Material* basicMat = new Material(shader);
        Texture* tex = new Texture("Assets/cube_initialShadingGroup_BaseColor.bmp", 2048, 2048, 8);
        basicMat->addTex("colorTexture", tex);


        Material* basicMatplane = new Material(shader);
        Texture* tex2 = new Texture("Assets/plane_initialShadingGroup_BaseColor.png", 2048, 2048, 8);
        basicMatplane->addTex("colorTexture", tex2);
        Cube* cube = new Cube(5);
        cube->setMat(basicMat);
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