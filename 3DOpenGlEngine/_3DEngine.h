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
#include "ParticleSystem.h"
#include "PolyGrid.h"
#include "ShaderLib.h"
#include "TextureLib.h"
#include "UiPlane.h"

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

	unsigned long int timeElapesed;
	unsigned long int timerunning;

	std::list<Renderable*> renderables_;
	std::list<ShaderProgram*> shaders;
	std::list<Updatable*> updatabels;
	std::list<UiPlane*> uiElements;
	std::list<void(*)(_3DEngine* engine)> updateFunctions;
	std::list<void(*)(GLFWwindow* window, int key, int scancode, int action, int mods)> keycallBacks;
	void static framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{

		_3DEngine* engine = _3DEngine::getInstance();
		std::cout << "test: " << width / (float)engine->width << std::endl;
		engine->updateUiRatio(Vector2f((float)engine->width / width, (float)engine->height / height));


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

	void static keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		_3DEngine* engine = _3DEngine::getInstance();
		for (void(*func)(GLFWwindow * window, int key, int scancode, int action, int mods) : engine->keycallBacks)
		{
			func(window, key, scancode, action, mods);
		}
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
		glfwSetKeyCallback(this->mainWindow, keyboard_callback);
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

	void iniitShaderLib()
	{
		ShaderLib::iniitShaderLib();
		this->addShader(ShaderLib::phongShader);
		this->addShader(ShaderLib::guideShader);
		this->addShader(ShaderLib::particleShader);
	}

	void initilizeGlad()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw std::runtime_error("couldnt intinlize glad");
		}
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}


	void cameraApplyMovement()
	{
		this->activeCamera->applyZoom(this->mouse->getScrollMovement());
//		std::cout << mouse->getIsLeftePressed() << std::endl;

		if(this->mouse->getIsLeftePressed())
		{
			this->activeCamera->applyMouseMovement(this->mouse->getMouseOffset()*Vector2f(width,height));
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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}




	void updateShaders()
	{
		for (ShaderProgram* shader : this->shaders)
		{
			shader->setCamera("camera", this->activeCamera);
			if(shader->isLightAffeted())
			{
				shader->applyLightData(activeCamera->getFullPositon());
			}
		}
	}






	void mainLoop()
	{


		unsigned long int timer; 
		

		while(!this->shouldClose)
		{
			timer = clock();
			processInput();
			clear();
			

			this->updateShaders();
			this->render();
			this->update();


			//activeCamera->rotateY(0.1);



			
			glfwSwapBuffers(this->mainWindow);
			if (glfwWindowShouldClose(this->mainWindow))
			{
				this->shouldClose = true;
			}
			this->resetOneTimeEvenets();
			timerunning = clock();
			timeElapesed = timerunning - timer;
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


	void update()
	{
		for (void(*funciton)(_3DEngine* engine) : updateFunctions)
		{
			funciton(this);
		}

		for (Updatable* element : updatabels)
		{
			element->update(getTimeElapesed());
		}
	}

	void updateUiRatio(Vector2f scaleFactor)
	{
		for (UiPlane* element : this->uiElements)
		{
			std::cout<<"TeeeeeeeeL :"<<scaleFactor<<std::endl;
			element->scale(Vector3f(scaleFactor.x, scaleFactor.y, 1));
			//element->move(Vector3f((1- scaleFactor.x)*-1, 1-scaleFactor.y, 0));
		}
		
	}


public:

	~_3DEngine()
	{
		ShaderLib::uninnit();
	}

	void addUpdate(void(* funciton)(_3DEngine* engine))
	{
		updateFunctions.push_back(funciton);
	}

	void addKeyCallBack(void(* cube_key_callback)(GLFWwindow* window, int key, int scancode, int action, int mods))
	{
		keycallBacks.push_back(cube_key_callback);
	}

	void addUpdatable(Updatable* updatable)
	{
		this->updatabels.push_back(updatable);
	}

	void addUiElement(UiPlane* ui_plane)
	{
		if (this->width > this->height) {
			ui_plane->scale(Vector3f(this->height / (float)this->width, 1, 1));
		//	ui_plane->move(Vector3f((1 - (this->height / (float)this->width)) * -1, 0, 0));
		}
		else
		{
			ui_plane->scale(Vector3f(1, this->width / (float)this->height, 1));
			//ui_plane->move(Vector3f(0,1-(this->width / (float)this->height),0));
		}
		this->uiElements.push_back(ui_plane);
	}
		

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
		PolyGrid* polygrid = new PolyGrid(10, 10, 10, 10);
		this->addRenderable(polygrid);
		polygrid->setMat(new Material(ShaderLib::guideShader));
		polygrid->set_render_mode(GL_LINE);
		polygrid->init();
	}

	void iniit(int windowWidth, int windowHeight)
	{
		this->initilizeOpenGl();
		this->initlizeWindow(windowWidth, windowHeight);
		this->initilizeGlad();
		this->initlizeCamera();
		this->iniitShaderLib();
		TextureLib::initTextureLib();
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


	float getTimeRunnig()
	{
		return (float)timerunning / CLOCKS_PER_SEC;
	}

	float getTimeElapesed()
	{
		return (float)timeElapesed / CLOCKS_PER_SEC;
	}
};

