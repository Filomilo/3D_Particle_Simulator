#include "ParticleSolver.h"
#include  "ParticleSystem.h"




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
		for (Point* pt : particle_system_->points)
		{
			updatePos(pt, timeElpased);
			applyForces(pt, timeElpased);
			applyGround(pt);
		}
	}