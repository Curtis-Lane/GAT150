#pragma once

#include "Particle.h"

#include <vector>

namespace ane {
	class ParticleSystem {
		public:
			ParticleSystem() = default;
			ParticleSystem(int maxCount) {
				this->particles.resize(maxCount);
			}

			void Update(float deltaTime);
			void Draw(class Renderer& renderer);

			Particle* GetFreeParticle();

		private:
			std::vector<Particle> particles;
	};

	extern ParticleSystem globalParticleSystem;
}