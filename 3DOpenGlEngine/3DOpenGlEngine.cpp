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


        Cube* cube = new Cube(0.5);
        cube->setShader(shader);
        cube->initilizePolygonal();




        cube->set_position(Vector3f(0, 0.5, 0));
        cube->set_rotation(Vector3f(45, 9, 0));
        engine->addRenderable(cube);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
       // engine->addRenderable(rectangle);
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