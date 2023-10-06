#pragma once
#include <list>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Vector4f.h"
#include <stdexcept>
#include "Renderable.h"
#include "ShaderProgram.h"
#include "Camera.h"
class _3DEngine
{

private:

	static _3DEngine* instance;
	GLFWwindow* mainWindow;
	bool shouldClose=false;
	Vector4f backgroundColor=Vector4f(0.1f,0.1f,0.1f,1.0f);
	Camera* activeCamera;
	int width;
	int height;



	std::list<Renderable*> renderables_;
	std::list<ShaderProgram*> shaders;

	void initilizeOpenGl()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	


	}

	void initlizeWindow(int windowWidth, int windowHeight)
	{
		this->width = windowWidth;
		this->height = windowHeight;
		this->mainWindow=  glfwCreateWindow(windowWidth, windowHeight, "3DEngine", NULL, NULL);
		if(mainWindow==NULL)
		{
			glfwTerminate();
			throw std::runtime_error("Error creating glfwWindow");
		}
		glfwMakeContextCurrent(this->mainWindow);
	}


	void initilizeGlad()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw std::runtime_error("couldnt intinlize glad");
		}
	}

	void processInput()
	{
		
	}

	void clear()
	{
		glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	glClear(GL_COLOR_BUFFER_BIT);
	}

	void startLoop()
	{
		processInput();
		clear();
	}


	void endLoop()
	{
		glfwPollEvents();
		glfwSwapBuffers(this->mainWindow);
		if (glfwWindowShouldClose(this->mainWindow))
		{
			this->shouldClose = true;
		}

	}


	void updateShaders()
	{
		for (ShaderProgram* shader : this->shaders)
		{
			shader->setCamera("camera", this->activeCamera);
		}
	}






	void mainLoop()
	{



		

		while(!this->shouldClose)
		{
			startLoop();
			

			this->updateShaders();
			this->render();
			

			endLoop();
		}
	}


	
	_3DEngine()
	{
		
	}

	void render()
	{
		for (Renderable* element : this->renderables_)
		{
			element->render();
		}
	}


public:

	static _3DEngine* getInstance()
	{
		if (_3DEngine::instance == nullptr)
		{
			return new _3DEngine;
		}
		return _3DEngine::instance;
	}

	void initlizeCamera()
	{
		this->activeCamera = new Camera(80, this->width / height, 0.01, 1000);
		this->activeCamera->set_position(Vector3f(0, 2,-10));
	}

	void iniit(int windowWidth, int windowHeight)
	{
		this->initilizeOpenGl();
		this->initlizeWindow(windowWidth, windowHeight);
		this->initilizeGlad();
		this->initlizeCamera();
	}


	void start()
	{
		this->mainLoop();
	}

	void addRenderable(Renderable* object)
	{
		this->renderables_.push_back(object);
	}

	void addShader(ShaderProgram* shader)
	{
		this->shaders.push_back(shader);
	}

};

