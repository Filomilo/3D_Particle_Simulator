#pragma once
#include <forward_list>
#include <list>

#include "Force.h"
#include "Point.h"
#include "Updatable.h"


class ParticleSystem;

class ParticleSolver:
public Updatable
{
private:
	ParticleSystem* particle_system_;
	std::list<Force*> forces;

	void updatePos(Point* pt, float timeElpased);

	void applyForces(Point* pt, float timeElpased)
	{
		for (Force* force: forces)
		{
			force->affect(pt, timeElpased);
		}
	}

public:
	void update(float timeElpased) override;


	ParticleSystem* get_particle_system() const
	{
		return particle_system_;
	}

	void set_particle_system(ParticleSystem* particle_system)
	{
		particle_system_ = particle_system;
	}


	void addForce(Force* force)
	{
		this->forces.push_back(force);
	}

};

