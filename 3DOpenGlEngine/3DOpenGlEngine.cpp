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
        Polygonal* rectangle = new Polygonal();
        rectangle->addPoints({
           {  0.5f,  0.5f, 0.0f},  // top right
             {0.5f, -0.5f, 0.0f},  // bottom right
            {-0.5f, -0.5f, 0.0f},  // bottom left
            {-0.5f,  0.5f, 0.0f},
             {-0.3f,  0.8f, 0.0f}
            });
        rectangle->addVertecies({ 0,1,2,3,4 });
        rectangle->addFace({ 0,1,2,3,4 });




        ShaderProgram* shader = new ShaderProgram("simpleVertexShader.vert", "simpleFragmentShader.frag");
       // shader->addAttribute("P", Attribute::VECTOR3F);
        rectangle->setShader(shader);
        rectangle->initilizePolygonal();
        engine->addRenderable(rectangle);
       engine->start();
    }
    catch (std::exception e)
    {
        std::cerr << e.what();
    }
}

int main()
{
    cubeTest();
	//Test();
    return 0;
}