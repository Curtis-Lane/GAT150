#include "EnginePhysicsComponent.h"

#include "Framework/Actor.h"

namespace ane {
	CLASS_DEFINITION(EnginePhysicsComponent);

	void EnginePhysicsComponent::Update(float deltaTime) {
		this->owner->transform.position += this->velocity * deltaTime;
		this->velocity *= std::pow(1.0f - this->damping, deltaTime);
	}

	void EnginePhysicsComponent::ApplyForce(const Vector2& force) {
		this->velocity += force;
	}
}
