// 3DOpenGlEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <glad/glad.h>

#include "_3DEngine.h"

int main()
{
    _3DEngine* engine = _3DEngine::getInstance();
    engine->iniit(800, 600);
    engine->start();
  
    return 0;
}