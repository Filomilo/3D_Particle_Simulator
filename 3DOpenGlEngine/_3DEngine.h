/**
 * @file _3DEngine.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file containg main 3d engie class
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
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
#include "UiSystem.h"
#include "Keyboard.h"
#include <time.h>
/**
 * @brief main 3d egninge class
 * 
 * 3d engine class coanitng all oject ot be rneder simualted updated nad runs main loop for handling al renders and updates
 * it is suing singleton so it can be sued everywhere
 */
class _3DEngine
{

private:
/**
 * @brief object instance
 * 
 */
	static _3DEngine* instance;
	/**
	 * @brief main opengl window
	 * 
	 */
	GLFWwindow* mainWindow;
	/**
	 * @brief if window shold close
	 * 
	 */
	bool shouldClose=false;
	/**
	 * @brief background color
	 * 
	 */
	Vector4f backgroundColor=Vector4f(0.1f,0.1f,0.1f,1.0f);
	/**
	 * @brief camera used for rendering
	 * 
	 */
	Camera* activeCamera;
	/**
	 * @brief width of windwo
	 * 
	 */
	int width;
	/**
	 * @brief height of window
	 * 
	 */
	int height;
	/**
	 * @brief mouse object for handling mouse states
	 * 
	 */
	Mouse* mouse=new Mouse();
	/**
	 * @brief if simualitno shoudl be run
	 * 
	 */
	bool isSimulationActive = false;
/**
 * @brief time esaplesd from prevois loop
 * 
 */
	unsigned long int timeElapesed;
	/**
	 * @brief time engine is runngin
	 * 
	 */
	unsigned long int timerunning;
/**
 * @brief list of renderables to be render
 * 
 */
	std::list<std::shared_ptr<Renderable> > renderables_;
	/**
	 * @brief list of sahders to be updated
	 * 
	 */
	std::list<ShaderProgram*> shaders;
	/**
	 * @brief list of updateable object to updated
	 * 
	 */
	std::list<std::shared_ptr<Updatable>> updatabels;
	/**
	 * @brief list of simualtables to simulated
	 * 
	 */
	std::list<std::shared_ptr<Simulatable>> simulatables;
	/**
	 * @brief elemnts of ui to be drawn on screen indepednely
	 * 
	 */
	std::list<std::shared_ptr<UiPlane>> uiElements;
	/**
	 * @brief keybboard object to handle keyboard input
	 * 
	 */
	Keyboard* keyboard=new Keyboard;
	/**
	 * @brief update funciton to be caled 
	 * 
	 */
	std::list<void(*)(_3DEngine* engine)> updateFunctions;
	/**
	 * @brief key callbascks to be called on eky input
	 * 
	 */
	std::list<void(*)(GLFWwindow* window, int key, int scancode, int action, int mods)> keycallBacks;
	/**
	 * @brief call back to be called on scrren reisze
	 * 
	 * @param window 
	 * @param width 
	 * @param height 
	 */
	void static framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{

		_3DEngine* engine = _3DEngine::getInstance();
		//std::cout << "test: " << width / (float)engine->width << std::endl;
		engine->updateUiRatio(Vector2f((float)engine->width / width, (float)engine->height / height));


		engine->width = width;
		engine->height = height;
		glViewport(0,0,width, height);

		engine->activeCamera->set_aspect(width, height);
	}
/**
 * @brief cal back to be called on mouse postion change
 * 
 * @param window 
 * @param x 
 * @param y 
 */
	void static cursor_pos_callback(GLFWwindow* window, double x, double y)
	{
		_3DEngine* engine = _3DEngine::getInstance();
		engine->mouse->setMousePostition(engine->width, engine->height, x, y);
	}
/**
 * @brief callback to be called on scroll movment
 * 
 * @param window 
 * @param x 
 * @param y 
 */
	void static scroll_callback(GLFWwindow* window, double x, double y)
	{
		_3DEngine* engine = _3DEngine::getInstance();
		engine->mouse->updateScroll(y);
		//std::cout << x << ", " << y << std::endl;
	}
	/**
	 * @brief mouse buton callback to be called on moue button press
	 * 
	 * @param window 
	 * @param button 
	 * @param action 
	 * @param mods 
	 */
	void static mouse_button_callback(GLFWwindow* window, int button,int action,int mods )
	{
		_3DEngine* engine = _3DEngine::getInstance();
		engine->mouse->updateMouseButton(button, action);
		//std::cout << button << ", " << action << ", " << mods << std::endl;
	}
	/**
	 * @brief keyboard callback ot be called on key input
	 * 
	 * @param window 
	 * @param key 
	 * @param scancode 
	 * @param action 
	 * @param mods 
	 */

	void static keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		_3DEngine* engine = _3DEngine::getInstance();
		for (void(*func)(GLFWwindow * window, int key, int scancode, int action, int mods) : engine->keycallBacks)
		{
			func(window, key, scancode, action, mods);
		}
		engine->keyboard->update(key, action);
	}
/**
 * @brief method taht reset one time events after loop
 * 
 */
	void resetOneTimeEvenets()
	{
		this->mouse->reset();
		keyboard->reset();
		
	}
/**
 * @brief Set the Call Backs objectmethod that set up callback for events
 * 
 */
	void setCallBacks()
	{
		glfwSetFramebufferSizeCallback(this->mainWindow, _3DEngine::framebuffer_size_callback);
		glfwSetCursorPosCallback(this->mainWindow, _3DEngine::cursor_pos_callback);
		glfwSetScrollCallback(this->mainWindow, _3DEngine::scroll_callback);
		glfwSetMouseButtonCallback(this->mainWindow, _3DEngine::mouse_button_callback);
		glfwSetKeyCallback(this->mainWindow, keyboard_callback);
	}


/**
 * @brief method that intlizes opnegl to workiwht
 * 
 */
	void initilizeOpenGl()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
	}
/**
 * @brief method that intlizs windwo to work with
 * 
 * @param windowWidth 
 * @param windowHeight 
 */
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
/**
 * @brief method taht intlizes shader library
 * 
 */
	void iniitShaderLib()
	{
		ShaderLib::iniitShaderLib();
		this->addShader(ShaderLib::phongShader);
		this->addShader(ShaderLib::guideShader);
		this->addShader(ShaderLib::particleShader);
		this->addShader(ShaderLib::particleShaderInstanced);
	}
/**
 * @brief method that intilzies glad librarry
 * 
 */
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

/**
 * @brief method that applyies camera movemrnt form user input
 * 
 */
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
/**
 * @brief method for porssing input events
 * 
 */
	void processInput()
	{
		glfwPollEvents();
		cameraApplyMovement();
	}
/**
 * @brief mrthod that clears render buffers
 * 
 */
	void clear()
	{
		glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}



/**
 * @brief method that updates shaders in library
 * 
 */
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



/**
 * @brief main loop for all of procceeses
 * 
 */
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


	/**
	 * @brief Construct a new 3dengine object
	 * 
	 */
	_3DEngine()
	{
		
	}
/**
 * @brief method taht render all renderables
 * 
 */
	void render()
	{
		for (std::shared_ptr<Renderable>  element : this->renderables_)
		{
			element->render();
		}
	}

/**
 * @brief method taht call all update functions and updates all objects
 * 
 */
	void update()
	{
		for (void(*funciton)(_3DEngine* engine) : updateFunctions)
		{
			funciton(this);
		}

		for (std::shared_ptr<Updatable> element : updatabels)
		{
			element->update(getTimeElapesed());
		}
	}
/**
 * @brief method that updates ui raiton for gui
 * 
 * @param scaleFactor 
 */
	void updateUiRatio(Vector2f scaleFactor)
	{
		for (std::shared_ptr<UiPlane> element : this->uiElements)
		{
			
			//<<"TeeeeeeeeL :"<<scaleFactor<<std::endl;
			element->scale(Vector3f(scaleFactor.x/ scaleFactor.y, 1, 1));
	
		}
		
	}


public:
/**
 * @brief Destroy the 3dengine object
 * 
 */
	~_3DEngine()
	{
		ShaderLib::uninnit();
	}
/**
 * @brief add updatable object
 * 
 * @param funciton 
 */
	void addUpdate(void(* funciton)(_3DEngine* engine))
	{
		updateFunctions.push_back(funciton);
	}
/**
 * @brief adds key callbakc
 * 
 * @param cube_key_callback 
 */
	void addKeyCallBack(void(* cube_key_callback)(GLFWwindow* window, int key, int scancode, int action, int mods))
	{
		keycallBacks.push_back(cube_key_callback);
	}
/**
 * @brief add updatable object
 * 
 * @param updatable 
 */
	void addUpdatable(std::shared_ptr<Updatable> updatable)
	{
		this->updatabels.push_back(updatable);
	}
/**
 * @brief adds ui elemtn 
 * 
 * @param ui_plane 
 */
	void addUiElement(std::shared_ptr<UiPlane> ui_plane)
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
		
/**
 * @brief Get the Instance object
 * 
 * @return _3DEngine* 
 */
	static _3DEngine* getInstance()
	{
		if (_3DEngine::instance == nullptr)
		{
			_3DEngine::instance= new _3DEngine;
			return _3DEngine::instance;
		}
		return _3DEngine::instance;
	}
/**
 * @brief inirlizes camera for opengl
 * 
 */
	void initlizeCamera()
	{
		this->activeCamera = new Camera(80, this->width / height, 0.01, 1000);
		this->activeCamera->moveIndendent(Vector3f(0, 6,-10));
		
	}
/**
 * @brief inrlizes ground for perspecitive
 * 
 */
	void initlizeGround()
	{
		std::shared_ptr<PolyGrid> polygrid = std::make_shared<PolyGrid>(10, 10, 10, 10);
		this->addRenderable(polygrid);
		polygrid->setMat(std::make_shared<Material>(ShaderLib::guideShader));
		polygrid->set_render_mode(GL_LINE);
		polygrid->init();
	}
/**
 * @brief inrlizes whole engine
 * 
 * @param windowWidth 
 * @param windowHeight 
 */
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

/**
 * @brief start main loop
 * 
 */
	void start()
	{
		this->mainLoop();
	}
/**
 * @brief add renderable object
 * 
 * @param object 
 */
	void addRenderable( std::shared_ptr<Renderable> object)
	{
		this->renderables_.push_back(object);
	}
/**
 * @brief add sahder to be handled
 * 
 * @param shader 
 */
	void addShader(ShaderProgram* shader)
	{
		this->shaders.push_back(shader);
	}

/**
 * @brief Get the Time Runnig object
 * 
 * @return float 
 */
	float getTimeRunnig()
	{
		return (float)timerunning / CLOCKS_PER_SEC;
	}
/**
 * @brief Get the Time Elapesed object
 * 
 * @return float 
 */
	float getTimeElapesed()
	{
		return (float)timeElapesed / CLOCKS_PER_SEC;
	}

/**
 * @brief Get the Key Board object
 * 
 * @return Keyboard* 
 */
	static Keyboard*  getKeyBoard()
	{
		return _3DEngine::getInstance()->keyboard;
	}
/**
 * @brief Get the Is Simulation Active object
 * 
 * @return true 
 * @return false 
 */
	bool getIsSimulationActive() {
		return isSimulationActive;
	}
/**
 * @brief get if siunumaltion is active
 * 
 */
	void inverseSimulationActive() {
		isSimulationActive = !isSimulationActive;
		std::cout << isSimulationActive << std::endl;
	}
/**
 * @brief clears al simulations
 * 
 */
	void clearSimulation()
	{
		for (std::shared_ptr<Simulatable> simulatable : simulatables)
		{
			simulatable->reset();
		}
	}
/**
 * @brief adds simualtables
 * 
 * @param element 
 */
	void addSimulatable(std::shared_ptr<Simulatable> element)
	{
		addUpdatable(element);
	  this->simulatables.push_back(element);
	}

};
