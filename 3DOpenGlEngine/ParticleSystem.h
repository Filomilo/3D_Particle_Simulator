#pragma once
#include "ParticleSolver.h"
#include "PointGroup.h"
#include "PointGroupInstanced.h"
#include "ShaderLib.h"
#include "Updatable.h"

class ParticleSystem :
    public PointGroupInstanced,
	public Updatable
{
private:




public:

	friend ParticleSolver;
	ParticleSystem(): PointGroupInstanced()
	{
	}

	ParticleSystem(std::shared_ptr<Polygonal> instance): PointGroupInstanced()
	{
		setInstanceGeo(instance);
		set_usage(GL_DYNAMIC_DRAW);
		setMat(std::make_shared<Material> (ShaderLib::particleShaderInstanced));
		init();
	}


	void addPoint(float pos, float color, float velocity, float size, float x, float x1, float x2)
	{
		PointGroup::addPoint(pos, color, velocity, size, x, x1, x2);
	}

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


	 void clearPoints();

};

