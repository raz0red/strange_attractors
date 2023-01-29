#ifndef ParticleSystem_hpp
#define ParticleSystem_hpp

#include "Trail.hpp"
#include "Particle.hpp"

using namespace cmn;

template <class T>
class ParticleSystem
{
private:
	T attractor;
	void drawParticles()
	{
		for (Particle *particle : Particle::getInstances())
		{
			Coordinate3f currPos = particle->getPosition();
			Coordinate3f newPos = attractor.updateCoordinate(currPos);
			particle->update(newPos);
			particle->draw();
		}
	};

public:
	void Tick()
	{
		drawParticles();
	};
};

#endif