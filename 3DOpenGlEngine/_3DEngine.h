#pragma once
#include <list>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Vector4f.h"
#include <stdexcept>
#include "Renderable.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Mouse.h"
#include "PolyGrid.h"

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
	Mouse* mouse=new Mouse();


	std::list<Renderable*> renderables_;
	std::list<ShaderProgram*> shaders;


	void static framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		_3DEngine* engine = _3DEngine::getInstance();
		engine->width = width;
		engine->height = height;
		glViewport(0,0,width, height);

		engine->activeCamera->set_aspect(width, height);
	}

	void static cursor_pos_callback(GLFWwindow* window, double x, double y)
	{
		_3DEngine* engine = _3DEngine::getInstance();
		engine->mouse->setMousePostition(engine->width, engine->height, x, y);
	}

	void static scroll_callback(GLFWwindow* window, double x, double y)
	{
		_3DEngine* engine = _3DEngine::getInstance();
		engine->mouse->updateScroll(y);
		std::cout << x << ", " << y << std::endl;
	}
	void static mouse_button_callback(GLFWwindow* window, int button,int action,int mods )
	{
		_3DEngine* engine = _3DEngine::getInstance();
		engine->mouse->updateMouseButton(button, action);
		//std::cout << button << ", " << action << ", " << mods << std::endl;
	}

	void resetOneTimeEvenets()
	{
		this->mouse->reset();
	}

	void setCallBacks()
	{
		glfwSetFramebufferSizeCallback(this->mainWindow, _3DEngine::framebuffer_size_callback);
		glfwSetCursorPosCallback(this->mainWindow, _3DEngine::cursor_pos_callback);
		glfwSetScrollCallback(this->mainWindow, _3DEngine::scroll_callback);
		glfwSetMouseButtonCallback(this->mainWindow, _3DEngine::mouse_button_callback);
	}



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


	void cameraApplyMovement()
	{
		this->activeCamera->applyZoom(this->mouse->getScrollMovement());
//		std::cout << mouse->getIsLeftePressed() << std::endl;

		if(this->mouse->getIsLeftePressed())
		{
			this->activeCamera->applyMouseMovement(this->mouse->getMouseOffset());
			//if(mouse->getMouseOffset().x!=0 || mouse->getMouseOffset().y != 0)
		//	std::cout << activeCamera->get_rotation() << std::endl;
		}
		else
		{
			if(mouse->getIsRightPressed())
			{
				activeCamera->applyZoom(mouse->getMouseOffset().x * mouse->getMouseOffset().y*1000);
			}
			else
			{
				if(mouse->getIsMiddlePressedd())
				{


				}
			}


		}
			
	}

	void processInput()
	{
		glfwPollEvents();
		cameraApplyMovement();
	}

	void clear()
	{
		glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	glClear(GL_COLOR_BUFFER_BIT);
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
			processInput();
			clear();
			

			this->updateShaders();
			this->render();
			


			//activeCamera->rotateY(0.1);



			
			glfwSwapBuffers(this->mainWindow);
			if (glfwWindowShouldClose(this->mainWindow))
			{
				this->shouldClose = true;
			}
			this->resetOneTimeEvenets();
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
			_3DEngine::instance= new _3DEngine;
			return _3DEngine::instance;
		}
		return _3DEngine::instance;
	}

	void initlizeCamera()
	{
		this->activeCamera = new Camera(80, this->width / height, 0.01, 1000);
		this->activeCamera->moveIndendent(Vector3f(0, 6,-10));
		
	}

	void initlizeGround()
	{
		//PolyGrid* polygrid = new PolyGrid(10, 10, 10, 10);
		//this->addRenderable(polygrid);
		//polygrid->initilizePolygonal();
	}

	void iniit(int windowWidth, int windowHeight)
	{
		this->initilizeOpenGl();
		this->initlizeWindow(windowWidth, windowHeight);
		this->initilizeGlad();
		this->initlizeCamera();
		this->initlizeGround();
		framebuffer_size_callback(this->mainWindow, windowWidth, windowHeight);
		setCallBacks();
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

