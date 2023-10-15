#pragma once
#include "PointGroup.h"
#include "ShaderLib.h"
#include "Updatable.h"

class ParticleSystem :
    public PointGroup,
	public Updatable
{
public:
	ParticleSystem(): PointGroup()
	{
		set_usage(GL_DYNAMIC_DRAW);
		setMat(new Material(ShaderLib::particleShader));
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
		updateVbo();
	}

	 void addPoint(const Vector3f& pos, const Vector3f& color, const Vector3f& velocity, float size)
	{
		Point* pt = new Point(pos);
		pt->setColor(color.r,color.g,color.b);
		pt->setVelocity(velocity.x, velocity.y, velocity.z);
		pt->setPscale(size);
		PointGroup::addPoint(pt);
	}
};
