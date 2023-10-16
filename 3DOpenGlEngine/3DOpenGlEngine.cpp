// 3DOpenGlEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <glad/glad.h>

#include "BoxEmitter.h"
#include "Cube.h"
#include "ParticleSystem.h"
#include "PhongMat.h"
#include "PointLight.h"
#include "ShaderProgram.h"
#include "_3DEngine.h"
#include "Gravity.h"
#include "Turbulance.h"


PointLight* pointLight;
Cube* cube;

void addPlane(_3DEngine* engine)
{
    PhongMat* basicMatplane = new PhongMat;
    basicMatplane->set_color_tex("Assets/plane_initialShadingGroup_BaseColor.png", 2048, 2048, 24);
    basicMatplane->set_normal_tex("Assets/plane_initialShadingGroup_Normal.png", 2048, 2048, 24);
    basicMatplane->set_rough_tex("Assets/plane_initialShadingGroup_Roughness.png", 2048, 2048, 8, GL_RED);

    PolyGrid* polygrid = new PolyGrid(20, 20, 2, 2);
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
    PhongMat* cubeMat = new PhongMat;
    cubeMat->set_color_tex("Assets/cube_initialShadingGroup_BaseColor.bmp", 2048, 2048, 24);
    cubeMat->set_normal_tex("Assets/cube_initialShadingGroup_Normal.bmp", 2048, 2048, 24);
    cubeMat->set_rough_tex("Assets/cube_initialShadingGroup_Roughness.bmp", 2048, 2048, 8, GL_RED);





     cube = new Cube(5);
    cube->setMat(cubeMat);
    cube->init();
    cube->moveY(2.501);
    engine->addRenderable(cube);
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
    pointLight = new PointLight;
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
       engine->start();
    }
    catch (std::exception e)
    {
        std::cerr <<"Error: "<< e.what();
    }
}
void particleTest()
{
    _3DEngine* engine = _3DEngine::getInstance();
    engine->iniit(800, 600);

    PointGroup* point_group = new PointGroup;
    srand(time(0));
    float particleSize = 100;
    for (int i = 0; i < 100000; i++)
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
    point_group->setMat(new Material(ShaderLib::particleShader));
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
    ParticleSystem* particle_system = new ParticleSystem;


    BoxEmitter* box_emitter = new BoxEmitter(Vector3f(0, 10, 0), Vector3f(10, 10, 10));
    box_emitter->set_particle_system(particle_system);
    engine->addUpdatable(box_emitter);

    engine->addUpdatable(particle_system);
    engine->addRenderable(particle_system);

    ParticleSolver* particle_solver = new ParticleSolver;
    particle_solver->set_particle_system(particle_system);
        engine->addUpdatable(particle_solver);
        particle_solver->addForce(new Gravity);
        particle_solver->addForce(new Turbulance);
    engine->start();
}


int main()
{
    //cubeTest();
	//particleTest();
   //emptyTest();
    SimulationTest();
    return 0;
}