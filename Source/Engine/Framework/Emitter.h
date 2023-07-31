#pragma once

#include "Actor.h"

#include "Core/Color.h"

namespace ane {
	struct EmitterData {
		// Emission
		float spawnRate = 0.0f;
		float spawnRateTimer = 0.0f;
		bool burst = false;
		size_t burstCount = 0;

		// Particle Parameters
		float lifeTimeMin = 0.0f;
		float lifeTimeMax = 0.0f;
		float speedMin = 0.0f;
		float speedMax = 0.0f;
		float damping = 0.0f;
		float angle = 0.0f;
		float angleRange = 0.0f;
		Color color;
	};

	class Emitter : public Actor {
		public:
			Emitter() = default;
			Emitter(const class Transform& transform, const EmitterData& data) :
				Actor{transform} {
				this->data = data;
			}

			void Update(float deltaTime);
			void Draw(class Renderer& renderer) {;}

		private:
			void Emit();

		private:
			EmitterData data;
	};
}