#pragma once

#include "Component.h"

namespace ane {
	class CollisionComponent : public Component {
		public:
			virtual bool CheckCollision(CollisionComponent* collision) = 0;

		public:
			float radius = 0.0f;
	};
}