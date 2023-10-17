#pragma once
#include <forward_list>
#include <list>
#include <vector>

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


	float groundLevel = 0;


	void applyGround(Point* pt)
	{
		Vector3f* pos = (Vector3f*)pt->getAttribute("P");
		if(pos->y<=groundLevel)
		{
			pos->y = groundLevel;
			Vector3f* vel = (Vector3f*)pt->getAttribute("V");
			Float* bounce=(Float*)pt->getAttribute("bounce");
			vel->y *= -1 * bounce->x;
		}
	}


	bool applyDecay(std::vector<Point*>::iterator pt, float timeElpased);

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

