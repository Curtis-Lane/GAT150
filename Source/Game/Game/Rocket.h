#pragma once

#include "Framework/Actor.h"
#include "Audio/AudioSystem.h"

class Rocket : public ane::Actor {
	public:
	Rocket(float speed, const ane::Transform& transform, std::shared_ptr<ane::Model> model, const std::string& fireSound) :
		ane::Actor(transform, model) {
		this->speed = speed;
		this->lifeSpan = 2.0f;
		ane::globalAudioSystem.PlayOneShot(fireSound);
	}

	void Update(float deltaTime) override;
	void OnCollision(Actor* other) override;

	private:
		float speed = 0.0f;
		float turnRate = 0.0f;
};