#include "Enemy.h"

#include "Player.h"
#include "Rocket.h"
#include "Framework/Framework.h"

bool Enemy::Initialize() {
	Actor::Initialize();

	ane::CollisionComponent* collisionComponent = GetComponent<ane::CollisionComponent>();
	if(collisionComponent != nullptr) {
		ane::RenderComponent* renderComponent = GetComponent<ane::RenderComponent>();
		if(renderComponent != nullptr) {
			float scale = this->transform.scale;
			collisionComponent->radius = renderComponent->GetRadius() * scale;
		}
	}

	return true;
}

void Enemy::Update(float deltaTime) {
	Actor::Update(deltaTime);

	ane::vec2 forward = ane::vec2(0, -1).Rotate(this->transform.rotation);

	Player* player = this->scene->GetActor<Player>();
	if(player != nullptr) {
		ane::Vector2 direction = player->transform.position - this->transform.position;

		// Turn towards player
		float turnAngle = ane::vec2::SignedAngle(forward, direction.Normalized());
		this->transform.rotation += turnAngle * deltaTime;
		
		// Check if we are facing the player
		if(std::fabs(turnAngle) < ane::DegreesToRadians(30.0f)) {
			// I seeeee youuuuuu
			this->fireTimer -= deltaTime;
		}
	}

	this->transform.position += forward * speed * ane::globalTime.GetDeltaTime();
	this->transform.position.x = ane::Wrap(this->transform.position.x, static_cast<float> (ane::globalRenderer.GetWidth()));
	this->transform.position.y = ane::Wrap(this->transform.position.y, static_cast<float> (ane::globalRenderer.GetHeight()));

	//this->fireTimer -= deltaTime;
	if(this->fireTimer <= 0) {
		this->fireTimer = this->fireRate;
		// Fire weapon
		ane::Transform rocketTransform(this->transform.position, this->transform.rotation, this->transform.scale * 0.66f);
		std::unique_ptr<Rocket> rocket = std::make_unique<Rocket>(400.0f, rocketTransform, "zombie_hurt1");
		rocket->tag = "Enemy";
		// Create components
		std::unique_ptr<ane::SpriteComponent> component = std::make_unique<ane::SpriteComponent>();
		component->texture = ane::globalResourceManager.Get<ane::Texture>("arrow.png", ane::globalRenderer);
		rocket->AddComponent(std::move(component));

		std::unique_ptr<ane::CircleCollisionComponent> collisionComponent = std::make_unique<ane::CircleCollisionComponent>();
		collisionComponent->radius = 30.0f;
		rocket->AddComponent(std::move(collisionComponent));

		rocket->Initialize();

		this->scene->Add(std::move(rocket));
	}
}

void Enemy::OnCollision(Actor* other) {
	if(dynamic_cast<Rocket*>(other) != nullptr && other->tag == "Player") {
		health -= 10;
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

			data.color = ane::Color(0.1258133f, 0.6178572f, 0.0f, 1.0f);

			ane::Transform transform(this->transform.position, 0, 1);
			std::unique_ptr<ane::Emitter> emitter = std::make_unique<ane::Emitter>(transform, data);
			emitter->lifeSpan = 0.5f;
			this->scene->Add(std::move(emitter));

			ane::globalAudioSystem.PlayOneShot("zombie_death");
		}

		this->destroyed = true;
	}
}
