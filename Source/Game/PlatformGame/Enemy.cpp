#include "Enemy.h"

#include "Framework/Framework.h"
#include "Player.h"

CLASS_DEFINITION(Enemy);

bool Enemy::Initialize() {
	Actor::Initialize();

	// Cache off
	this->physicsComponent = GetComponent<ane::PhysicsComponent>();

	return true;
}

void Enemy::Update(float deltaTime) {
	Actor::Update(deltaTime);

	ane::vec2 forward = ane::vec2(1.0f, 0.0f).Rotate(this->transform.rotation);

	Player* player = this->scene->GetActor<Player>();
	if(player != nullptr) {
		ane::Vector2 direction = player->transform.position - this->transform.position;

		// Move towards player
		this->physicsComponent->ApplyForce(direction.Normalized() * this->speed);
	}
}

void Enemy::OnCollisionEnter(Actor* other) {
	//if(other->tag == "Player") {
	//	health -= 10;
	//}

	if(health <= 0) {
		if(!this->destroyed) {
			EVENT_DISPATCH("OnEnemyDead", 0);
		}

		this->destroyed = true;
	}
}

void Enemy::OnCollisionExit(Actor* other) {
	//
}

void Enemy::Read(const ane::JSON_t& value) {
	Actor::Read(value);

	READ_DATA(value, speed);
	READ_DATA(value, health);
}
