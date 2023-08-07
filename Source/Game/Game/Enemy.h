#pragma once

#include "Framework/Actor.h"

class Enemy : public ane::Actor {
	public:
		Enemy(float speed, float turnRate, const ane::Transform& transform) :
			ane::Actor(transform) {
			this->speed = speed;
			this->turnRate = turnRate;
			this->fireRate = 0.5f;
			this->fireTimer = this->fireRate;
		}

		void Update(float deltaTime) override;
		void OnCollision(Actor* other) override;

	private:
		float speed = 0.0f;
		float turnRate = 0.0f;
		int health = 25;

		float fireRate = 0.0f;
		float fireTimer = 0.0f;
};