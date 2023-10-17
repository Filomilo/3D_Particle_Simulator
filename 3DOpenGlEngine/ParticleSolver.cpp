#include "ParticleSolver.h"
#include  "ParticleSystem.h"
#include "Attribute.h"
#include "Float.h"


void ParticleSolver::updatePos(Point* pt, float timeElpased)
{
	Vector3f* pos = (Vector3f*)pt->getAttribute("P");
	Vector3f* V = (Vector3f*)pt->getAttribute("V");
	pos->x += V->x* timeElpased;
	pos->y += V->y * timeElpased;
	pos->z += V->z * timeElpased;
}

	void ParticleSolver::update(float timeElpased) 
	{
		int ptNum = 0;
		for (std::vector<Point*>::iterator  pt = this->particle_system_->points.begin(); pt != this->particle_system_->points.end(); ) 
		{
				if (applyDecay(pt, timeElpased))
					break;

			updatePos(*pt, timeElpased);
			applyForces(*pt, timeElpased);
			applyGround(*pt);
			++pt;
		}
	}


	bool ParticleSolver::applyDecay(std::vector<Point*>::iterator pt, float timeElpased)
	{
		(*pt)->increaseAge(timeElpased);
		Float* age = (Float*)(*pt)->getAttribute("age");
		Float* life = (Float*)(*pt)->getAttribute("life");
		if (life->x < age->x)
		{
			this->particle_system_->points.erase(pt);
			return true;
		}
		return false;
	}