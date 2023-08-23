#pragma once

#include "Framework/Actor.h"

#include <vector>

#include "Framework/Components/PhysicsComponent.h"

class Player : public ane::Actor {
	public:
		enum class Powerups {
			DoubleShot,
			SlowMo
		};

	public:
		CLASS_DECLARATION(Player);

		bool Initialize() override;
		void Update(float deltaTime) override;
		void OnCollision(Actor* other) override;

		friend class SpaceGame;

	private:
		float speed = 0.0f;
		float turnRate = 0.0f;
		int health = 100;

		std::vector<Powerups> powerups;

		ane::PhysicsComponent* physicsComponent = nullptr;
};