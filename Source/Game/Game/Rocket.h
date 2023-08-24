#pragma once

#include "Framework/Components/PhysicsComponent.h"
#include "Framework/Actor.h"

class Rocket : public ane::Actor {
	public:
		CLASS_DECLARATION(Rocket);

		bool Initialize() override;
		void Update(float deltaTime) override;

		void OnCollisionEnter(Actor* other);

	private:
		float speed = 0.0f;
		ane::PhysicsComponent* physicsComponent = nullptr;
};
