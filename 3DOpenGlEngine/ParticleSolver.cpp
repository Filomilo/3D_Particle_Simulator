#include "ParticleSolver.h"
#include  "ParticleSystem.h"
#include "Attribute.h"
#include "Float.h"


void ParticleSolver::updatePos(std::shared_ptr<Point> pt, float timeElpased)
{
	 std::shared_ptr<Vector3f> pos = std::dynamic_pointer_cast <Vector3f>(pt->getAttribute("P"));
	 std::shared_ptr<Vector3f> V = std::dynamic_pointer_cast <Vector3f>(pt->getAttribute("V"));
	pos->x += V->x* timeElpased;
	pos->y += V->y * timeElpased;
	pos->z += V->z * timeElpased;
}

	void ParticleSolver::update(float timeElpased) 
	{
		int ptNum = 0;
		for (std::vector<std::shared_ptr<Point>>::iterator  pt = this->particle_system_->points.begin(); pt != this->particle_system_->points.end(); ) 
		{
				if (applyDecay(pt, timeElpased))
					break;

			updatePos(*pt, timeElpased);
			applyForces(*pt, timeElpased);
			applyGround(*pt);
			++pt;
		}
	}


	bool ParticleSolver::applyDecay(std::vector<std::shared_ptr<Point>>::iterator pt, float timeElpased)
	{
		(*pt)->increaseAge(timeElpased);
		std::shared_ptr<Float> age = std::dynamic_pointer_cast <Float>((*pt)->getAttribute("age"));
		std::shared_ptr<Float> life = std::dynamic_pointer_cast <Float>((*pt)->getAttribute("life"));
		if (life->x < age->x)
		{
			this->particle_system_->points.erase(pt);
			return true;
		}
		return false;
	}