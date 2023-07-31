#include "ParticleSystem.h"

namespace ane {
	ParticleSystem globalParticleSystem(100);

	void ParticleSystem::Update(float deltaTime) {
		for(Particle& particle : this->particles) {
			if(particle.isActive) {
				particle.Update(deltaTime);
			}
		}
	}

	void ParticleSystem::Draw(Renderer& renderer) {
		for(Particle& particle : this->particles) {
			if(particle.isActive) {
				particle.Draw(renderer);
			}
		}
	}

	Particle* ParticleSystem::GetFreeParticle() {
		for(Particle& particle : this->particles) {
			if(!particle.isActive) {
				return &particle;
			}
		}

		return nullptr;
	}
}