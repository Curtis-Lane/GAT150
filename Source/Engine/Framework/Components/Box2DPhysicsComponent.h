#pragma once

#include "Physics/PhysicsSystem.h"
#include "PhysicsComponent.h"

class b2Body;

namespace ane {
	class Box2DPhysicsComponent : public PhysicsComponent {
		public:
			CLASS_DECLARATION(Box2DPhysicsComponent)

			bool Initialize() override;
			void OnDestroy() override;

			void Update(float deltaTime) override;
			virtual void ApplyForce(const Vector2& force) override;
			virtual void ApplyTorque(float torque) override;

			friend class Box2DCollisionComponent;

		private:
			PhysicsSystem::RigidBodyData data;
			b2Body* body = nullptr;
	};
}