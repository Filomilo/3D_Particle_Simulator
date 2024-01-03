/**
 * @file ParticleSystem.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file containing calss paritcle system
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include "ParticleSolver.h"
#include "PointGroup.h"
#include "PointGroupInstanced.h"
#include "ShaderLib.h"
#include "Sphere.h"
#include "Updatable.h"

/**
 * @brief class with particle system
 * 
 * clas handles instance point group taht is updatable
 * 
 */
class ParticleSystem :
    public PointGroupInstanced,
	public Updatable
{
private:




public:

	friend ParticleSolver;

/**
 * @brief Construct a new Particle System object
 * 
 * cretes paritcel system with already defined instance geometry
 * 
 * @param instance 
 */
	ParticleSystem(std::shared_ptr<Polygonal> instance): PointGroupInstanced()
	{
		setInstanceGeo(instance);
		set_usage(GL_DYNAMIC_DRAW);
		setMat(std::make_shared<Material> (ShaderLib::particleShaderInstanced));
		init();
	}
	/**
	 * @brief Construct a new Particle System object
	 * 
	 * created basci paritcle system with no defined yet instance geo
	 * 
	 */
	ParticleSystem() : PointGroupInstanced()
	{
		std::shared_ptr<Sphere> sph = std::make_shared<Sphere>(0.06, 10, 20);
		sph->setMat(std::make_shared<Material>(ShaderLib::particleShader)); \
			sph->init();
		setInstanceGeo(sph);
		set_usage(GL_DYNAMIC_DRAW);
		setMat(std::make_shared<Material>(ShaderLib::particleShaderInstanced));
		init();
	}
/**
 * @brief add points like in point group class
 * 
 * 
 * not sute why this was here
 * 
 * @param pos 
 * @param color 
 * @param velocity 
 * @param size 
 * @param x 
 * @param x1 
 * @param x2 
 */
	void addPoint(float pos, float color, float velocity, float size, float x, float x1, float x2)
	{
		PointGroup::addPoint(pos, color, velocity, size, x, x1, x2);
	}
/**
 * @brief update vertedx buffer of object
 * 
 * @param timeElpased 
 */
	void update(float timeElpased) override
	{
		/*
		float particleSize = 10;
		this->addPoint(
			Vector3f(
			(float)rand() / RAND_MAX * particleSize - particleSize / 2,
			(float)rand() / RAND_MAX * particleSize - particleSize / 2,
			(float)rand() / RAND_MAX * particleSize - particleSize / 2
				)
			,
			Vector3f((float)rand() / RAND_MAX,
			(float)rand() / RAND_MAX,
			(float)rand() / RAND_MAX
		),
			Vector3f((float)rand() / RAND_MAX,
				(float)rand() / RAND_MAX,
				(float)rand() / RAND_MAX
			),
			(float)rand() / RAND_MAX * 50
		);
		*/
		updateVboInstanced();
	}
/**
 * @brief add point with specifed apramters
 * 
 * @param pos postion of point
 * @param color color of point
 * @param velocity velocity of point
 * @param size size of point
 * @param mass mass of point
 * @param bounce bouncienns of point
 * @param life life pf point
 */
	 void addPoint(const Vector3f& pos, const Vector3f& color, const Vector3f& velocity, float size=1, float mass=1, float bounce=1.0, float life=10)
	{

		std::shared_ptr<Point> pt = std::make_shared<Point>(pos);
		pt->setColor(color.r,color.g,color.b);
		pt->setVelocity(velocity.x, velocity.y, velocity.z);
		pt->setPscale(size);
		pt->setMass(mass);
		pt->setBounce(bounce);
		pt->setLife(life);
		PointGroup::addPoint(pt);
	}

/**
 * @brief method that removes vurrently handled points
 * 
 */
	 void clearPoints();

};

