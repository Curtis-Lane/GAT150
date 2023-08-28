#pragma once

#include "Framework/Actor.h"

#include "Framework/Components/PhysicsComponent.h"

class Player : public ane::Actor {
	public:
		CLASS_DECLARATION(Player);

		bool Initialize() override;
		void Update(float deltaTime) override;

		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;

	private:
		float speed = 0.0f;
		float jump = 0.0f;
		int health = 100;
		int groundCount = 0;

		ane::PhysicsComponent* physicsComponent;
};