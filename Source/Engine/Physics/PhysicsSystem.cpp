#include "PhysicsSystem.h"

namespace ane {
	bool PhysicsSystem::Initialize() {
		b2Vec2 gravity(0.0f, 10.0f);
		this->world = std::make_unique<b2World>(gravity);

		return true;
	}

	void PhysicsSystem::Update(float deltaTime) {
		//
	}
}