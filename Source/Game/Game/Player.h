#pragma once

#include "Framework/Actor.h"

#include <vector>

class Player : public ane::Actor {
	public:
		enum class Powerups {
			DoubleShot,
			SlowMo
		};

	public:
		Player(float speed, float turnRate, const ane::Transform& transform, std::shared_ptr<ane::Model> model) :
			ane::Actor(transform, model) {
			this->speed = speed;
			this->turnRate = turnRate;
		}

		void Update(float deltaTime) override;
		void OnCollision(Actor* other) override;

		friend class SpaceGame;

	private:
		float speed = 0.0f;
		float turnRate = 0.0f;
		int health = 100;

		std::vector<Powerups> powerups;
};