#pragma once

#include "Framework/Actor.h"

class Rocket : public ane::Actor {
	public:
		CLASS_DECLARATION(Rocket);

		bool Initialize() override;

		void Update(float deltaTime) override;
		void OnCollision(Actor* other);

	private:
		float speed = 0.0f;
};
