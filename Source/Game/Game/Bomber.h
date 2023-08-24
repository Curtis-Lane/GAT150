#pragma once

#include "Framework/Actor.h"

#include "Framework/Components/PhysicsComponent.h"

class Bomber : public ane::Actor {
	public:
		CLASS_DECLARATION(Bomber);

		bool Initialize() override;

		void Update(float deltaTime) override;
		void OnCollisionEnter(Actor* other) override;

	private:
		float speed = 0.0f;
		float turnRate = 0.0f;
		int health = 15;

		ane::PhysicsComponent* physicsComponent = nullptr;
};