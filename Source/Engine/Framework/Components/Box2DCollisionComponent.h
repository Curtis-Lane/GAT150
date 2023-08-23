#pragma once

#include "CollisionComponent.h"

#include <functional>

#include "Physics/PhysicsSystem.h"

namespace ane {
	class Box2DCollisionComponent : public CollisionComponent {
		public:
			using collisionFunction = std::function<void(Actor*)>;

		public:
			CLASS_DECLARATION(Box2DCollisionComponent)

			virtual bool Initialize() override;
			virtual void Update(float deltaTime) override;

		private:
			PhysicsSystem::CollisionData data;
			Vector2 scaleOffset = Vector2(1, 1);
	};
}