#pragma once

#include "Component.h"

#include "Core/Vector2.h"

namespace ane {
	class PhysicsComponent : public Component {
		public:
			virtual void ApplyForce(const Vector2& force) = 0;

		public:
			Vector2 velocity;
			Vector2 acceleration;
			float mass = 1.0f;
			float damping = 0.0f;
	};
}