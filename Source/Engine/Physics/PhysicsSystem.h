#pragma once

#include "Framework/Singleton.h"

#include <memory>

#include <box2d/include/box2d/box2d.h>

#include "Core/Math/Vector2.h"
#include "ContactListener.h"

#define VEC2_TO_B2VEC2(vec) (*(b2Vec2*)(&vec))
#define B2VEC2_TO_VEC2(vec) (*(ane::Vector2*)(&vec))

namespace ane {
	class PhysicsSystem : public Singleton<PhysicsSystem> {
		public:
			struct RigidBodyData {
				float gravityScale = 1.0f;
				float damping = 0.0f;
				float angularDamping = 0.0f;
				bool constrainAngle = false;
				bool isDynamic = true;
			};

			struct CollisionData {
				Vector2 size;
				Vector2 offset;
				float density = 1;
				float friction = 1;
				float restitution = 0.3f;
				bool isTrigger = false;
			};

		public:
			bool Initialize();

			void Update(float deltaTime);

			b2Body* CreateBody(const Vector2& position, float angle, const RigidBodyData& data);
			void DestroyBody(b2Body* body);
 
			void SetCollisionBox(b2Body* body, const CollisionData& data, class Actor* actor = nullptr);
			void SetCollisionBoxStatic(b2Body* body, const CollisionData& data, class Actor* actor = nullptr);
 
			Vector2 WorldToScreen(const Vector2& world) {return world * this->pixelsPerUnit;}
			Vector2 ScreenToWorld(const Vector2& screen) {return screen * (1.0f / this->pixelsPerUnit);}

			friend Singleton;

		private:
			PhysicsSystem() = default;

		private:
			float pixelsPerUnit = 48.0f;

			std::unique_ptr<b2World> world;
			std::unique_ptr<ContactListener> contactListener;
	};
}