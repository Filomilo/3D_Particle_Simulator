#pragma once
#include "ParticleSystem.h"
#include "Transformable.h"
#include "Updatable.h"
#include <math.h>
class Emitter :
    public Transformable,
	public Updatable,
	public Parametrized
{
    virtual Vector3f getNewPointPosition() = 0;
    virtual Vector3f getNewColor() = 0;
    virtual Vector3f getNewVelocity() = 0;
    virtual float getNewSize() = 0;

private:
    std::shared_ptr<Float> particles_per_second=std::make_shared<Float>(10);

    std::shared_ptr<ParticleSystem> particle_system;

    float timeBuffer=0;
  
    int calculatePartceToCreate(float time_elpased)
    {
        timeBuffer += time_elpased;
        float seconddivcision = 1.0 / particles_per_second->x;
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
	    return particles_per_second->x;
    }

    void set_particles_per_second(unsigned particles_per_second)
    {
	    this->particles_per_second->x = particles_per_second;
    }

    std::shared_ptr<ParticleSystem> get_particle_system() const
    {
	    return particle_system;
    }

    void set_particle_system(std::shared_ptr<ParticleSystem> particle_system)
    {
	    this->particle_system = particle_system;
    }

    std::shared_ptr<UiParameterGroup> getParameterGroup() override
    {
        std::shared_ptr<UiParameterGroup> ui_parameter_group = std::make_shared<UiParameterGroup>("Gravity");
        ui_parameter_group->addParameter(std::make_shared <UiParameter>("paritcles_per_Second", this->particles_per_second, 1));
        return ui_parameter_group;
    }
};

