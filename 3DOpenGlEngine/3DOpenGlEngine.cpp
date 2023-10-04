// 3DOpenGlEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "myWindow", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Error creating window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    while (1)
    {

    }
    return 0;
}