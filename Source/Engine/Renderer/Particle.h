#pragma once

#include "Core/Vector2.h"
#include "Core/Color.h"

namespace ane {
	struct ParticleData {
		vec2 position;
		vec2 prevPosition;
		vec2 velocity;
		float damping = 0.0f;

		Color color;

		float lifeTimer = 0.0f;
		float lifeTime = 0.0f;
	};

	class Particle {
		public:
			Particle() = default;

			void Initialize(const ParticleData& data) {
				this->data = data;
				this->isActive = true;
			}
			void Update(float deltaTime);
			void Draw(class Renderer& renderer);

			friend class ParticleSystem;

		private:
			ParticleData data;
			bool isActive = false;
	};
}