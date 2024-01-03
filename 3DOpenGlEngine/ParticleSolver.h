/**
 * @file ParticleSolver.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief a file conating paritcle sovler
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once
#include <forward_list>
#include <list>
#include <vector>

#include "Force.h"
#include "Point.h"
#include "Updatable.h"
#include "Simulatable.h"

class ParticleSystem;
/**
 * @brief paritlce solver class
 * class that handles siumalting specifed particle system
 */
class ParticleSolver:
public Simulatable
{
private:
/**
 * @brief particle system that is being simulated
 * 
 */
	std::shared_ptr<ParticleSystem> particle_system_;
	/**
	 * @brief list coinatining forces to applies in simulation
	 * 
	 */
	std::list<std::shared_ptr<Force>> forces;
/**
 * @brief updated postion of point based on vleocity and time isnce last update
 * 
 * @param pt point to be updated
 * @param timeElpased time since last loop
 */
	void updatePos(std::shared_ptr<Point> pt, float timeElpased);
/**
 * @brief a method that apllies forces to point
 * 
 * @param pt point to be apply to
 * @param timeElpased time sicne alst update
 */
	void applyForces(std::shared_ptr<Point> pt, float timeElpased)
	{
		for (std::shared_ptr<Force> force: forces)
		{
			force->affect(pt, timeElpased);
		}
	}


	float groundLevel = 0;

/**
 * @brief apply ground level to points
 * 
 * @param pt point to be udpated
 */
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

/**
 * @brief applied decaing of paritcel over time
 * not used
 * 
 * @param pt point to be applied to 
 * @param timeElpased time since alst update
 * @return true 
 * @return false 
 */
	bool applyDecay(std::vector<std::shared_ptr<Point>>::iterator pt, float timeElpased);

public:
/**
 * @brief main update emthod to update siumaltion
 * 
 * @param timeElpased 
 */
	void update(float timeElpased) override;

/**
 * @brief Get the particle system objectr
 * 
 * 
 * 
 * @return std::shared_ptr<ParticleSystem> 
 */
	std::shared_ptr<ParticleSystem> get_particle_system() const
	{
		return particle_system_;
	}
/**
 * @brief Set the particle system object
 * 
 * @param particle_system 
 */
	void set_particle_system(std::shared_ptr<ParticleSystem> particle_system)
	{
		particle_system_ = particle_system;
	}

/**
 * @brief add force to list
 * 
 * @param force 
 */
	void addForce(std::shared_ptr<Force> force)
	{
		this->forces.push_back(force);
	}
/**
 * @brief reset simulaiton
 * 
 */
	void reset();

};

