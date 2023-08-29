#include "Player.h"

#include "Framework/Framework.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"

CLASS_DEFINITION(Player);

bool Player::Initialize() {
	Actor::Initialize();

	// Cache off
	this->physicsComponent = GetComponent<ane::PhysicsComponent>();
	this->spriteAnimRenderComponent = GetComponent<ane::SpriteAnimRenderComponent>();

	return true;
}

void Player::Update(float deltaTime) {
	Actor::Update(deltaTime);

	// Movement
	float dir = 0.0f;
	if(ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_A) || ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_LEFT)) {
		dir = -1.0f;
	} else if(ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_D) || ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_RIGHT)) {
		dir = 1.0f;
	}

	ane::vec2 forward = ane::vec2(1.0f, 0.0f).Rotate(this->transform.rotation);

	this->physicsComponent->ApplyForce(forward * this->speed * dir * ((this->groundCount > 0) ? 1 : 0.75f));

	// Jump
	if(ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !ane::globalInputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
		ane::Vector2 up = ane::Vector2(0, -1);

		if(this->groundCount > 0) {
			this->physicsComponent->SetVelocity(up * this->jump);
		}
	}

	// Animation
	ane::Vector2 velocity = this->physicsComponent->velocity;
	// Check if moving
	if(std::fabs(velocity.x) > 0.2f && dir != 0) {
		this->spriteAnimRenderComponent->flipH = (velocity.x < -0.1f);
		this->spriteAnimRenderComponent->SetSequence("run");
	} else {
		this->spriteAnimRenderComponent->SetSequence("idle");
	}
}

void Player::OnCollisionEnter(Actor* other) {
	if(other->tag == "Ground") {
		groundCount++;
	}

	//if(other->tag == "Enemy") {
	//	health -= 10;
	//}

	if(health <= 0) {
		if(!this->destroyed) {
			EVENT_DISPATCH("OnPlayerDead", 0);
		}

		this->destroyed = true;
	}
}

void Player::OnCollisionExit(Actor* other) {
	if(other->tag == "Ground") {
		groundCount--;
	}
}

void Player::Read(const ane::JSON_t& value) {
	Actor::Read(value);

	READ_DATA(value, speed);
	READ_DATA(value, jump);
	READ_DATA(value, health);
}
