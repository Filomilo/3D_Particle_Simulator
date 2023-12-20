#pragma once
#include <forward_list>
#include <list>
#include <vector>

#include "Force.h"
#include "Point.h"
#include "Updatable.h"
#include "Simulatable.h"

class ParticleSystem;

class ParticleSolver:
public Simulatable
{
private:
	std::shared_ptr<ParticleSystem> particle_system_;
	std::list<std::shared_ptr<Force>> forces;

	void updatePos(std::shared_ptr<Point> pt, float timeElpased);

	void applyForces(std::shared_ptr<Point> pt, float timeElpased)
	{
		for (std::shared_ptr<Force> force: forces)
		{
			force->affect(pt, timeElpased);
		}
	}


	float groundLevel = 0;


	void applyGround(std::shared_ptr<Point> pt)
	{
		 std::shared_ptr<Vector3f> pos = std::dynamic_pointer_cast<Vector3f>(pt->getAttribute("P"));
		if(pos->y<=groundLevel)
		{
			pos->y = groundLevel;
			 std::shared_ptr<Vector3f> vel = std::dynamic_pointer_cast<Vector3f>(pt->getAttribute("V"));
			std::shared_ptr<Float> bounce= std::dynamic_pointer_cast<Float>(pt->getAttribute("bounce"));
			vel->y *= -1 * bounce->x;
		}
	}


	bool applyDecay(std::vector<std::shared_ptr<Point>>::iterator pt, float timeElpased);

public:
	void update(float timeElpased) override;


	std::shared_ptr<ParticleSystem> get_particle_system() const
	{
		return particle_system_;
	}

	void set_particle_system(std::shared_ptr<ParticleSystem> particle_system)
	{
		particle_system_ = particle_system;
	}


	void addForce(std::shared_ptr<Force> force)
	{
		this->forces.push_back(force);
	}

	void reset();

};

