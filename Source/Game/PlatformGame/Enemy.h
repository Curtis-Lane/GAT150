#pragma once

#include "Framework/Actor.h"

#include "Framework/Components/PhysicsComponent.h"

class Enemy : public ane::Actor {
	public:
		CLASS_DECLARATION(Enemy);

		bool Initialize() override;
		void Update(float deltaTime) override;

		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;

	private:
		float speed = 0.0f;
		int health = 100;
		float invulnTime = 0.0f;
		float currentInvulnTime = 0.0f;

		ane::PhysicsComponent* physicsComponent = nullptr;
};