#pragma once
#include "Point.h"
#include "Updatable.h"


class ParticleSystem;

class ParticleSolver:
public Updatable
{
private:
	ParticleSystem* particle_system_;

	void updatePos(Point* pt, float timeElpased);
	
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
};

