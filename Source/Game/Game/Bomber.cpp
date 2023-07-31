#include "Bomber.h"

#include "Player.h"
#include "Rocket.h"
#include "Framework/Game.h"
#include "Framework/Scene.h"
#include "Framework/Emitter.h"

void Bomber::Update(float deltaTime) {
	Actor::Update(deltaTime);

	ane::vec2 forward = ane::vec2(0, -1).Rotate(this->transform.rotation);

	Player* player = this->scene->GetActor<Player>();
	if(player != nullptr) {
		ane::Vector2 direction = player->transform.position - this->transform.position;

		// Turn towards player
		float turnAngle = ane::vec2::SignedAngle(forward, direction.Normalized());
		this->transform.rotation += turnAngle * deltaTime;
	}

	this->transform.position += forward * speed * ane::globalTime.GetDeltaTime();
	this->transform.position.x = ane::Wrap(this->transform.position.x, static_cast<float> (ane::globalRenderer.GetWidth()));
	this->transform.position.y = ane::Wrap(this->transform.position.y, static_cast<float> (ane::globalRenderer.GetHeight()));
}

void Bomber::OnCollision(Actor* other) {
	if(dynamic_cast<Rocket*>(other) != nullptr && other->tag == "Player") {
		this->health -= 10;
	} else if(dynamic_cast<Player*>(other) != nullptr && other->tag == "Player") {
		this->health = 0;
	}

	if(health <= 0) {
		this->game->AddPoints(100);

		if(!this->destroyed) {
			// Spawn particles when an enemy dies
			ane::EmitterData data;
			data.burst = true;
			data.burstCount = 100;
			//data.spawnRate = 200.0f;
			data.angle = 0.0f;
			data.angleRange = ane::Pi;
			data.lifeTimeMin = 0.5f;
			data.lifeTimeMax = 1.5f;
			data.speedMin = 50.0f;
			data.speedMax = 250.0f;
			data.damping = 0.5f;

			data.color = ane::Color(0.25f, 1.0f, 0.0f, 1.0f);

			ane::Transform transform(this->transform.position, 0, 1);
			std::unique_ptr<ane::Emitter> emitter = std::make_unique<ane::Emitter>(transform, data);
			emitter->lifeSpan = 0.5f;
			this->scene->Add(std::move(emitter));

			ane::globalAudioSystem.PlayOneShot("creeper_death");
		}

		this->destroyed = true;
	}
}
