#include "Player.h"

#include "Framework/Framework.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"

CLASS_DEFINITION(Player);

bool Player::Initialize() {
	Actor::Initialize();

	EVENT_SUBSCRIBE("OnAnimationEnd", Player::OnAnimationEnd);

	// Cache off
	this->physicsComponent = GetComponent<ane::PhysicsComponent>();
	this->spriteAnimRenderComponent = GetComponent<ane::SpriteAnimRenderComponent>();

	return true;
}

void Player::Update(float deltaTime) {
	Actor::Update(deltaTime);

	ane::Vector2 velocity = this->physicsComponent->velocity;
	bool onGround = (this->groundCount > 0);

	if(!this->busy) {
		// Movement
		float dir = 0.0f;
		if(ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_A) || ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_LEFT)) {
			dir = -1.0f;
		} else if(ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_D) || ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_RIGHT)) {
			dir = 1.0f;
		}

		if(dir != 0) {
			velocity.x += this->speed * dir * ((onGround) ? 1 : 0.75f) * deltaTime;
			velocity.x = ane::Clamp(velocity.x, -this->maxSpeed, this->maxSpeed);
			this->physicsComponent->SetVelocity(velocity);
		}

		// Jump
		if(ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !ane::globalInputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
			ane::Vector2 up = ane::Vector2(0, -1);

			if(onGround) {
				this->physicsComponent->SetVelocity(velocity + (up * this->jump));
			}
		}

		this->physicsComponent->SetGravityScale((velocity.y > 0) ? 3 : 2);

		// Animation
		// Check if moving
		if(std::fabs(velocity.x) > 0.2f && dir != 0) {
			this->spriteAnimRenderComponent->flipH = (velocity.x < -0.1f);
			this->spriteAnimRenderComponent->SetSequence("run");
		} else {
			if(!this->swordDrawn) {
				this->spriteAnimRenderComponent->SetSequence("idle");
			} else {
				this->spriteAnimRenderComponent->SetSequence("idle_sword");
			}
		}

		if(ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_E) && onGround) {
			if(!this->swordDrawn) {
				this->busy = true;
				this->spriteAnimRenderComponent->SetSequence("draw_sword");
			} else {
				this->busy = true;
				this->spriteAnimRenderComponent->SetSequence("sheath_sword");
			}
		}

		if(ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_F) && onGround && this->swordDrawn) {
			if(this->attackFrame == 0) {
				this->busy = true;
				this->spriteAnimRenderComponent->SetSequence("attack1");
			} else if(this->attackFrame == 1) {
				this->busy = true;
				this->spriteAnimRenderComponent->SetSequence("attack2");
			} else if(this->attackFrame == 2) {
				this->busy = true;
				this->spriteAnimRenderComponent->SetSequence("attack3");
			}
		}

		if(attackFrame != 0) {
			attackFrame = 0;
		}
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

void Player::OnAnimationEnd(const ane::Event& event) {
	std::string animation = std::get<std::string>(event.data);
	//std::cout << animation << std::endl;
	if(animation == "draw_sword") {
		this->swordDrawn = true;
		this->busy = false;
	} else if(animation == "sheath_sword") {
		this->swordDrawn = false;
		this->busy = false;
	}

	if(animation == "attack1") {
		this->attackFrame = 1;
		this->busy = false;
	} else if(animation == "attack2") {
		this->attackFrame = 2;
		this->busy = false;
	} else if(animation == "attack3") {
		this->attackFrame = 3;
		this->busy = false;
	}
}

void Player::Read(const ane::JSON_t& value) {
	Actor::Read(value);

	READ_DATA(value, speed);
	READ_DATA(value, maxSpeed);
	READ_DATA(value, jump);
	READ_DATA(value, health);
}
