#pragma once

#include "Framework/Singleton.h"

#include <memory>

#include <box2d/include/box2d/b2_world.h>

namespace ane {
	class PhysicsSystem : public Singleton<PhysicsSystem> {
		public:
			bool Initialize();

			void Update(float deltaTime);

			friend Singleton;

		private:
			PhysicsSystem() = default;

		private:
			std::unique_ptr<b2World> world;
	};
}