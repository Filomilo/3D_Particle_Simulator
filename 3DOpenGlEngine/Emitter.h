#pragma once
#include "ParticleSystem.h"
#include "Transformable.h"
#include "Updatable.h"
#include <math.h>
class Emitter :
    public Transformable,
	public Updatable
{
    virtual Vector3f getNewPointPosition() = 0;
    virtual Vector3f getNewColor() = 0;
    virtual Vector3f getNewVelocity() = 0;
    virtual float getNewSize() = 0;

private:
    unsigned int particles_per_second=10;

    ParticleSystem* particle_system;

    float timeBuffer=0;
  
    int calculatePartceToCreate(float time_elpased)
    {
        timeBuffer += time_elpased;
        float seconddivcision = 1.0 / particles_per_second;
        int amtTocreate = floor(timeBuffer / seconddivcision);
        timeBuffer -= seconddivcision * amtTocreate;
        return amtTocreate;
    }
public:
   

    void update(float timeElpased) override
    {


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
                getNewSize()
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

    unsigned get_particles_per_second() const
    {
	    return particles_per_second;
    }

    void set_particles_per_second(unsigned particles_per_second)
    {
	    this->particles_per_second = particles_per_second;
    }

    ParticleSystem* get_particle_system() const
    {
	    return particle_system;
    }

    void set_particle_system(ParticleSystem* particle_system)
    {
	    this->particle_system = particle_system;
    }
};

