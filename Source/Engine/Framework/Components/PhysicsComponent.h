#pragma once

#include "Core/Math/Vector2.h"
#include "Component.h"

namespace ane {
	class PhysicsComponent : public Component {
		public:
			virtual void ApplyForce(const Vector2& force) = 0;
			virtual void ApplyTorque(float torque) = 0;
			virtual void SetVelocity(const Vector2& velocity) {this->velocity = velocity;}

		public:
			Vector2 velocity;
			Vector2 acceleration;
			float mass = 1.0f;
			float damping = 0.0f;
	};
}