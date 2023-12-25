

#include <glad/glad.h>

#include "BoxEmitter.h"
#include "Cube.h"
#include "ParticleSystem.h"
#include "PhongMat.h"
#include "PointLight.h"
#include "ShaderProgram.h"
#include "_3DEngine.h"
#include "Gravity.h"
#include "TextureLib.h"
#include "Turbulance.h"
#include "UiPlane.h"
#include "UiSystem.h"
#include "UiText.h"
#include <sstream>
#include "Vortex.h"
#include "PointGroupInstanced.h"
#include "Sphere.h"

std::shared_ptr<PointLight> pointLight;
std::shared_ptr<Cube> cube;

void addPlane(_3DEngine* engine)
{
    std::shared_ptr<PhongMat> basicMatplane = std::make_shared<PhongMat>() ;
    basicMatplane->set_color_tex("Assets/plane_initialShadingGroup_BaseColor.png", 2048, 2048, 24);
    basicMatplane->set_normal_tex("Assets/plane_initialShadingGroup_Normal.png", 2048, 2048, 24);
    basicMatplane->set_rough_tex("Assets/plane_initialShadingGroup_Roughness.png", 2048, 2048, 8, GL_RED);

   std::shared_ptr<PolyGrid> polygrid = std::make_shared<PolyGrid> (20, 20, 2, 2);
    polygrid->setMat(basicMatplane);
    polygrid->init();
    engine->addRenderable(polygrid);
}
void cube_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    float speed = 0.1;
    Vector3f offset;
    Vector3f rotation;
    static bool Dhold = false, Ahold = false, Whold = false, Shold=false, SHIFThold = false, SPACEhold = false, Ehold = false, Rhold = false, Thold = false, Yhold = false;
    if (key == GLFW_KEY_D && action == GLFW_RELEASE)
        Dhold = false;
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
        Dhold = true;

    if (key == GLFW_KEY_A && action == GLFW_RELEASE)
        Ahold = false;
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        Ahold = true;

    if (key == GLFW_KEY_W && action == GLFW_RELEASE)
        Whold = false;
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        Whold = true;

    if (key == GLFW_KEY_S && action == GLFW_RELEASE)
        Shold = false;
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        Shold = true;

    if (key == GLFW_KEY_E && action == GLFW_RELEASE)
        Ehold = false;
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
        Ehold = true;

    if (key == GLFW_KEY_R && action == GLFW_RELEASE)
        Rhold = false;
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
        Rhold = true;

    if (key == GLFW_KEY_T && action == GLFW_RELEASE)
        Thold = false;
    if (key == GLFW_KEY_T && action == GLFW_PRESS)
        Thold = true;
    if (key == GLFW_KEY_Y && action == GLFW_RELEASE)
        Yhold = false;
    if (key == GLFW_KEY_Y && action == GLFW_PRESS)
        Yhold = true;

    if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE)
        SHIFThold = false;
    if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
        SHIFThold = true;


    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
        SPACEhold = false;
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        SPACEhold = true;
        


    if (Dhold)
        offset.x -= speed;
    if (Ahold)
        offset.x += speed;
    if (Whold)
        offset.z += speed;
    if (Shold)
        offset.z -= speed;

    if (SPACEhold)
        offset.y += speed;
    if (SHIFThold)
        offset.y -= speed;

    if (Ehold)
        rotation.x -= speed * 10;
    if (Rhold)
        rotation.x += speed * 10;
    if (Thold)
        rotation.z += speed * 10;
    if (Yhold)
        rotation.z -= speed*10;


        cube->move(offset);
        cube->rotateX(rotation.x);
        cube->rotateZ(rotation.z);
}
void addCube(_3DEngine* engine)
{
    std::shared_ptr<PhongMat> cubeMat = std::make_shared<PhongMat>();
    cubeMat->set_color_tex("Assets/cube_initialShadingGroup_BaseColor.bmp", 2048, 2048, 24);
    cubeMat->set_normal_tex("Assets/cube_initialShadingGroup_Normal.bmp", 2048, 2048, 24);
    cubeMat->set_rough_tex("Assets/cube_initialShadingGroup_Roughness.bmp", 2048, 2048, 8, GL_RED);





    cube = std::make_shared<Cube>(5);
    cube->setMat(cubeMat);
    cube->init();
    cube->moveY(2.501);
    engine->addRenderable(cube);
    engine->addKeyCallBack(cube_key_callback);

}








void addSphere(_3DEngine* engine)
{
    std::shared_ptr<PhongMat> sphereMat = std::make_shared<PhongMat>();
    sphereMat->set_color_tex("Assets/sph30_initialShadingGroup_BaseColor.png", 2048, 2048, 24);
    sphereMat->set_normal_tex("Assets/sph30_initialShadingGroup_Normal.png", 2048, 2048, 24);
    sphereMat->set_rough_tex("Assets/sph30_initialShadingGroup_Roughness.png", 2048, 2048, 8, GL_RED);
    sphereMat->set_emission_tex(std::make_shared < Texture>("Assets/sph30_initialShadingGroup_Emissive.png", 2048, 2048, 24));




    std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(3, 30, 30);
    sphere->setMat(sphereMat);
    sphere->init();
    sphere->move(Vector3f(5,3,5));
    engine->addRenderable(sphere);
    engine->addKeyCallBack(cube_key_callback);

}






void lightAround(_3DEngine* engine)
{

    Vector3f pos = pointLight->getFullPositon();
    float r = sqrt(pos.x * pos.x + pos.z * pos.z);
    float alpha = 0.01;
    //Vector3f newPos= Vector3f(r * cos(alpha), pos.y, r * sin(alpha));
    //pointLight->move(newPos-pos);
    float time = engine->getTimeRunnig();
    pointLight->set_position(Vector3f(sin(time)*5, pos.y,cos(time)*5));
    //pointLight->rota(0.1);
  //  pointLight->move(Vector3f(0.001, 0.001, 0));
}


void addLight(_3DEngine* engine)
{
    pointLight = std::make_shared<PointLight>();
    pointLight->move(Vector3f(0, 5, 5));
    Light::setAmbientColor(Vector3f(0.8, 0.8, 1));
    Light::setAmbientIntensity(0.4);
    engine->addRenderable(pointLight);
    engine->addUpdate(lightAround);
}



void cubeTest()
{
    try {
        _3DEngine* engine = _3DEngine::getInstance();
        engine->iniit(800, 600);
        addLight(engine);
        addCube(engine);
        addPlane(engine);
        addSphere(engine);
       engine->start();
    }
    catch (std::exception e)
    {
        std::cerr <<"Error: "<< e.what();
    }
}



void sphereTest()
{
    try {
        _3DEngine* engine = _3DEngine::getInstance();
        engine->iniit(800, 600);
        addLight(engine);
        


       

        std::shared_ptr<Sphere> cube = std::make_shared<Sphere>(5,8,15);
        cube-> setMat(std::make_shared<Material>(ShaderLib::particleShader));
        cube->init();
        cube->moveY(2.501);
        engine->addRenderable(cube);



        addPlane(engine);
        engine->start();
    }
    catch (std::exception e)
    {
        std::cerr << "Error: " << e.what();
    }
}

void particleTest()
{
    _3DEngine* engine = _3DEngine::getInstance();
    engine->iniit(800, 600);


    std::shared_ptr<PointGroup> point_group = std::make_shared<PointGroup>();
    srand(time(0));
    float particleSize = 100;
    for (int i = 0; i < 1000; i++)
    {
        point_group->addPoint(
            (float)rand() / RAND_MAX * particleSize - particleSize / 2,
            (float)rand() / RAND_MAX * particleSize - particleSize / 2,
            (float)rand() / RAND_MAX * particleSize - particleSize / 2,
            (float)rand() / RAND_MAX,
            (float)rand() / RAND_MAX,
            (float)rand() / RAND_MAX,
            (float)rand() / RAND_MAX*50
        );
    }
    point_group->setMat(std::make_shared<Material>(ShaderLib::particleShader));
    point_group->init();



    engine->addRenderable(point_group);


    engine->start();
}


void pointGroupInstanced()
{
	_3DEngine* engine = _3DEngine::getInstance();
	engine->iniit(800, 600);
	addCube(engine);
	addLight(engine);
	std::shared_ptr<PointGroupInstanced> point_group = std::make_shared<PointGroupInstanced>();
	point_group->setInstanceGeo(cube);
	srand(time(0));
	float particleSize = 100;
	for (int i = 0; i < 10000; i++)
	{
		point_group->addPoint(
			(float)rand() / RAND_MAX * particleSize - particleSize / 2,
			(float)rand() / RAND_MAX * particleSize - particleSize / 2,
			(float)rand() / RAND_MAX * particleSize - particleSize / 2,
			(float)rand() / RAND_MAX,
			(float)rand() / RAND_MAX,
			(float)rand() / RAND_MAX,
			(float)rand() / RAND_MAX * 50
		);
	}
	point_group->setMat(std::make_shared<Material>(ShaderLib::particleShaderInstanced));
	point_group->init();



	engine->addRenderable(point_group);
	
	//   addCube(engine);


	engine->start();
}


void emptyTest()
{
    _3DEngine* engine = _3DEngine::getInstance();
    engine->iniit(800, 600);
    engine->start();
}


void SimulationTest()
{
    _3DEngine* engine = _3DEngine::getInstance();
    engine->iniit(800, 600);
    //addCube(engine);

    std::shared_ptr<ParticleSystem> particle_system = std::make_shared<ParticleSystem>();
    

    std::shared_ptr < BoxEmitter> box_emitter = std::make_shared<BoxEmitter>(Vector3f(0, 10, 0), Vector3f(10, 10, 10));
    box_emitter->set_particle_system(particle_system);
    engine->addUpdatable(box_emitter);

    engine->addUpdatable(particle_system);
    engine->addRenderable(particle_system);

    std::shared_ptr < ParticleSolver> particle_solver = std::make_shared < ParticleSolver>();
    particle_solver->set_particle_system(particle_system);
        engine->addSimulatable(particle_solver);


        std::shared_ptr < Gravity> gravity = std::make_shared < Gravity>();
        std::shared_ptr <Turbulance> turbulance = std::make_shared < Turbulance>();
		std::shared_ptr <Vortex> vortex = std::make_shared < Vortex>();
		particle_solver->addForce(gravity);
        particle_solver->addForce(turbulance);
		particle_solver->addForce(vortex);
        


        std::shared_ptr<UiSystem> uisystem = std::make_shared<UiSystem>() ;
		
        uisystem->addParameterGroup(gravity->getParameterGroup());
        uisystem->addParameterGroup(turbulance->getParameterGroup());
        uisystem->addParameterGroup(box_emitter->getParameterGroup());
		uisystem->addParameterGroup(vortex->getParameterGroup());
        engine->addUiElement(uisystem);
        engine->addRenderable(uisystem);
        engine->addUpdatable(uisystem);

    engine->start();
}
std::shared_ptr<UiText> txt;



void SimulationTestInstance()
{
    _3DEngine* engine = _3DEngine::getInstance();
    engine->iniit(800, 600);
    addCube(engine);
    addLight(engine);
    std::shared_ptr<ParticleSystem> particle_system = std::make_shared<ParticleSystem>();
    particle_system->init();
    std::shared_ptr < BoxEmitter> box_emitter = std::make_shared<BoxEmitter>(Vector3f(0, 10, 0), Vector3f(10, 10, 10));
    box_emitter->set_particle_system(particle_system);
    engine->addUpdatable(box_emitter);

    engine->addUpdatable(particle_system);
    engine->addRenderable(particle_system);

    std::shared_ptr < ParticleSolver> particle_solver = std::make_shared < ParticleSolver>();
    particle_solver->set_particle_system(particle_system);
    engine->addSimulatable(particle_solver);


    std::shared_ptr < Gravity> gravity = std::make_shared < Gravity>();
    std::shared_ptr <Turbulance> turbulance = std::make_shared < Turbulance>();
    std::shared_ptr <Vortex> vortex = std::make_shared < Vortex>();
    particle_solver->addForce(gravity);
    particle_solver->addForce(turbulance);
    particle_solver->addForce(vortex);



    std::shared_ptr<UiSystem> uisystem = std::make_shared<UiSystem>();

    uisystem->addParameterGroup(gravity->getParameterGroup());
    uisystem->addParameterGroup(turbulance->getParameterGroup());
    uisystem->addParameterGroup(box_emitter->getParameterGroup());
    uisystem->addParameterGroup(vortex->getParameterGroup());
    engine->addUiElement(uisystem);
    engine->addRenderable(uisystem);
    engine->addUpdatable(uisystem);

    engine->start();
}

void udpateTxt(_3DEngine* engine)
{
    static int i = 1;
    std::stringstream text;
    
    text << clock();

		
        txt->setText(text.str());
    
i++;

}


void uiTest()
{
    _3DEngine* engine = _3DEngine::getInstance();
    engine->iniit(800, 600);
    ///std::shared_ptr<UiPlane> uiPlane = new UiPlane();
    //uiPlane->setTex(TextureLib::ArialFontTex);
    //engine->addUiElement(uiPlane);
   // engine->addRenderable(uiPlane);
    txt = std::make_shared<UiText>("lOspasdka sd",0.05);

   


     std::shared_ptr<UiSystem> uisystem = std::make_unique<UiSystem>();
     float AA=0;
     float BB=0;
     float CC=0;
     float DD=0;


     std::shared_ptr<UiParameterGroup> test = std::make_shared<UiParameterGroup>("test");
     std::shared_ptr<UiParameterGroup> dummy = std::make_shared<UiParameterGroup>("dummy");

    // test->addParameter(std::make_shared<UiParameter>("AA", &AA, 1));
    // test->addParameter(std::make_shared<UiParameter>("BB", &BB, 1));
    // dummy->addParameter(std::make_shared<UiParameter>("CC", &CC, 1));
   //  dummy->addParameter(std::make_shared<UiParameter>("DD", &DD, 1));


     uisystem->addParameterGroup(test);
     uisystem->addParameterGroup(dummy);
    // engine->addUpdate(udpateTxt);
     engine->addUpdatable(std::dynamic_pointer_cast<Updatable>(uisystem) );
     engine->addUiElement(std::dynamic_pointer_cast<UiPlane > (uisystem));
     engine->addRenderable(uisystem);
   // addCube(engine);
    engine->start();
}

void textTest()
{
    _3DEngine* engine = _3DEngine::getInstance();
    engine->iniit(800, 600);
    ///std::shared_ptr<UiPlane> uiPlane = new UiPlane();
    //uiPlane->setTex(TextureLib::ArialFontTex);
    //engine->addUiElement(uiPlane);
    
   // engine->addRenderable(uiPlane);
    txt = std::make_shared<UiText>("abcedlo: \n z bieba spadlo", 0.005);
    //txt = std::make_shared<UiText>("A", 0.05);
    engine->addUiElement(txt);
    engine->addRenderable(txt);

    // addCube(engine);
    engine->start();
}

int main()
{
 cubeTest();
//	particleTest();
//	pointGroupInstanced();
//emptyTest();
	//SimulationTest();
   // SimulationTestInstance();
  // uiTest();
   // textTest();
  //  sphereTest();
    return 0;
}