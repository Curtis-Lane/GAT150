#pragma once

#include "Framework/Actor.h"

#include "Framework/Components/PhysicsComponent.h"

class Enemy : public ane::Actor {
	public:
		CLASS_DECLARATION(Enemy);

		bool Initialize() override;

		void Update(float deltaTime) override;
		void OnCollision(Actor* other) override;

	private:
		float speed = 0.0f;
		float turnRate = 0.0f;
		int health = 25;

		float fireRate = 0.0f;
		float fireTimer = 0.0f;

		ane::PhysicsComponent* physicsComponent = nullptr;
};