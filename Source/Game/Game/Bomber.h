#pragma once

#include "Framework/Actor.h"

#include "Audio/AudioSystem.h"

class Bomber : public ane::Actor {
	public:
		Bomber(float speed, float turnRate, const ane::Transform& transform) :
			ane::Actor(transform) {
			this->speed = speed;
			this->turnRate = turnRate;
			ane::globalAudioSystem.PlayOneShot("creeper_hiss3");
		}

		bool Initialize() override;

		void Update(float deltaTime) override;
		void OnCollision(Actor* other) override;

	private:
		float speed = 0.0f;
		float turnRate = 0.0f;
		int health = 15;
};