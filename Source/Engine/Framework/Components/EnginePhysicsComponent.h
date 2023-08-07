#pragma once

#include "PhysicsComponent.h"

namespace ane {
	class EnginePhysicsComponent : public PhysicsComponent {
		public:
			virtual void Update(float deltaTime) override;
			virtual void ApplyForce(const Vector2& force) override;
	};
}