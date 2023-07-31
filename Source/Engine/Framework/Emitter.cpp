#include "Emitter.h"

#include "Renderer/ParticleSystem.h"

namespace ane {
	void Emitter::Update(float deltaTime) {
		Actor::Update(deltaTime);
		
		// Create burst particles
		if(this->data.burst) {
			this->data.burst = false;
			for(int i = 0; i < this->data.burstCount; i++) {
				Emit();
			}
		}

		// Create particles based on rate
		if(this->data.spawnRate > 0.0f) {
			this->data.spawnRateTimer += deltaTime;
			while(this->data.spawnRateTimer > 0) {
				Emit();
				this->data.spawnRateTimer -= (1 / this->data.spawnRate);
			}
		}
	}

	void Emitter::Emit() {
		Particle* particle = globalParticleSystem.GetFreeParticle();

		if(particle != nullptr) {
			ParticleData data;
			data.lifeTime = randomf(this->data.lifeTimeMin, this->data.lifeTimeMax);
			data.lifeTimer = 0.0f;
			data.position = this->transform.position;
			data.prevPosition = data.position;
			data.color = this->data.color;

			float angle = this->transform.rotation + this->data.angle + randomf(-this->data.angleRange, this->data.angleRange);
			vec2 direction = vec2(0, -1).Rotate(angle);
			data.velocity = direction * randomf(this->data.speedMin, this->data.speedMax);
			data.damping = this->data.damping;

			particle->Initialize(data);
		}
	}
}