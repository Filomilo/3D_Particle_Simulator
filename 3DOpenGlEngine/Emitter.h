/**
 * @file Emitter.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file coanitng emiter calss
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include "ParticleSystem.h"
#include "Transformable.h"
#include "Updatable.h"
#include <math.h>
#include "_3DEngine.h"
/**
 * @brief emtiter calss
 * emitter class if paramters that genretes particles 
 * 
 */
class Emitter :
    public Transformable,
	public Updatable,
	public Parametrized
{
	/**
	 * @brief Get the New Point Position object
	 * 
	 * @return Vector3f 
	 */
    virtual Vector3f getNewPointPosition() = 0;
	/**
	 * @brief Get the New Color object
	 * 
	 * @return Vector3f 
	 */
    virtual Vector3f getNewColor() = 0;
	/**
	 * @brief Get the New Velocity object
	 * 
	 * @return Vector3f 
	 */
    virtual Vector3f getNewVelocity() = 0;
	/**
	 * @brief Get the New Size object
	 * 
	 * @return float 
	 */
    virtual float getNewSize() = 0;



	

private:
/**
 * @brief paramters definend paritcles genretd in second
 * 
 */
    std::shared_ptr<Float> particles_per_second=std::make_shared<Float>(10);
	/**
	 * @brief paratems defnie life of gernted apritcles
	 * 
	 */
	std::shared_ptr<Float> life_of_particle = std::make_shared<Float>(1);
	/**
	 * @brief paramters defineg bounciness of generated particles
	 * 
	 */
	std::shared_ptr<Float> bounciness_of_particle = std::make_shared<Float>(0);
	/**
	 * @brief mass of genrted particels
	 * 
	 */
	std::shared_ptr<Float> mass_of_particle = std::make_shared<Float>(1);
	/**
	 * @brief size of genrated apritcles
	 * 
	 */
	std::shared_ptr<Float> size_of_particle = std::make_shared<Float>(100);
    /**
     * @brief partile system to generate particel into
     * 
     */
	std::shared_ptr<ParticleSystem> particle_system;
/**
 * @brief time buffer to gernate more apritcle if loop took to time
 * 
 */
    float timeBuffer=0;
  /**
   * @brief calcautes how amny paritcle should be genrated
   * 
   * @param time_elpased 
   * @return int 
   */
    int calculatePartceToCreate(float time_elpased)
    {
        timeBuffer += time_elpased;
        float seconddivcision = 1.0 / particles_per_second->x;
        int amtTocreate = floor(timeBuffer / seconddivcision);
        timeBuffer -= seconddivcision * amtTocreate;
        return amtTocreate;
    }
public:
   
/**
 * @brief updateds paritcle metter
 * 
 * @param timeElpased 
 */
    void update(float timeElpased) override
    {
		if (_3DEngine::getInstance()->getIsSimulationActive()) {

			float particleSize = 10;
			/*
			particle_system->addPoint(
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

			int amtToCreate = calculatePartceToCreate(timeElpased);
			for (int i = 0; i < amtToCreate; i++) {

				particle_system->addPoint(
					getNewPointPosition(),
					getNewColor(),
					getNewVelocity(),
					size_of_particle->x,
					mass_of_particle->x,
					bounciness_of_particle->x,
					life_of_particle->x
				);
				/*
				particle_system->addPoint(
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

			}
		}
    }
/**
 * @brief Get the particles per second object
 * 
 * @return unsigned 
 */
    unsigned get_particles_per_second() const
    {
	    return particles_per_second->x;
    }
/**
 * @brief Set the particles per second object
 * 
 * @param particles_per_second 
 */
    void set_particles_per_second(unsigned particles_per_second)
    {
	    this->particles_per_second->x = particles_per_second;
    }
/**
 * @brief Get the particle system object
 * 
 * @return std::shared_ptr<ParticleSystem> 
 */
    std::shared_ptr<ParticleSystem> get_particle_system() const
    {
	    return particle_system;
    }
/**
 * @brief Set the particle system object
 * 
 * @param particle_system 
 */
    void set_particle_system(std::shared_ptr<ParticleSystem> particle_system)
    {
	    this->particle_system = particle_system;
    }
/**
 * @brief Get the Parameter Group object
 * 
 * @return std::shared_ptr<UiParameterGroup> 
 */
    std::shared_ptr<UiParameterGroup> getParameterGroup() override
    {
        std::shared_ptr<UiParameterGroup> ui_parameter_group = std::make_shared<UiParameterGroup>("Emitter");
		ui_parameter_group->addParameter(std::make_shared <UiParameter>("life_of_particle", this->life_of_particle, 0.01));
        ui_parameter_group->addParameter(std::make_shared <UiParameter>("paritcles_per_Second", this->particles_per_second, 1));
		ui_parameter_group->addParameter(std::make_shared <UiParameter>("bounciness_of_particle", this->bounciness_of_particle, 0.01));
		ui_parameter_group->addParameter(std::make_shared <UiParameter>("mass_of_particle", this->mass_of_particle, 0.1));
		ui_parameter_group->addParameter(std::make_shared <UiParameter>("size_of_particle", this->size_of_particle, 100));

        return ui_parameter_group;
    }


};

