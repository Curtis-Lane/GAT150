#pragma once

#include "PhysicsComponent.h"

namespace ane {
	class EnginePhysicsComponent : public PhysicsComponent {
		public:
			CLASS_DECLARATION(EnginePhysicsComponent);

			virtual void Update(float deltaTime) override;
			virtual void ApplyForce(const Vector2& force) override;
			virtual void ApplyTorque(float torque) override;
	};
}