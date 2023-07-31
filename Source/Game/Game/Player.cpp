#include "Player.h"

#include "Input/InputSystem.h"
#include "Framework/Scene.h"
#include "SpaceGame.h"
#include "Rocket.h"
#include "Bomber.h"

void Player::Update(float deltaTime) {
	Actor::Update(deltaTime);

	float rotate = 0.0f;
	if(ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_A) || ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_LEFT)) {
		rotate += -1.0f;
	} else if(ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_D) || ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_RIGHT)) {
		rotate += 1.0f;
	}
	this->transform.rotation += rotate * turnRate * ane::globalTime.GetDeltaTime();

	float thrust = 0.0f;
	if(ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_W) || ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_UP)) {
		thrust = 1;
	} else if(ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_S) || ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_DOWN)) {
		thrust = -1;
	} else {
		thrust = 0;
	}

	// Fire weapon
	if(ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !ane::globalInputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
		// This funky bit of code basically just checks if the player has the DoubleShot powerup
		auto it = std::find(this->powerups.begin(), this->powerups.end(), Powerups::DoubleShot);

		if(it != this->powerups.end()) {
			ane::Transform rocketTransform1(this->transform.position, this->transform.rotation + ane::DegreesToRadians(10), this->transform.scale / 2);
			std::unique_ptr<Rocket> rocket = std::make_unique<Rocket>(400.0f, rocketTransform1, this->model, "bow");
			rocket->tag = "Player";
			this->scene->Add(std::move(rocket));

			ane::Transform rocketTransform2(this->transform.position, this->transform.rotation - ane::DegreesToRadians(10), this->transform.scale / 2);
			rocket = std::make_unique<Rocket>(400.0f, rocketTransform2, this->model, "bow");
			rocket->tag = "Player";
			this->scene->Add(std::move(rocket));
		} else {
			ane::Transform rocketTransform(this->transform.position, this->transform.rotation, this->transform.scale / 2);
			std::unique_ptr<Rocket> rocket = std::make_unique<Rocket>(400.0f, rocketTransform, this->model, "bow");
			rocket->tag = "Player";
			this->scene->Add(std::move(rocket));
		}
	}

	if(ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_T) || ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_LSHIFT) ||ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_RSHIFT)) {
		// This funky bit of code basically just checks if the player has the SlowMo powerup
		auto it = std::find(this->powerups.begin(), this->powerups.end(), Player::Powerups::SlowMo);

		if(it != this->powerups.end()) {
			ane::globalTime.SetTimeScale(0.5f);
		} else {
			ane::globalTime.SetTimeScale(1.0f);
		}
	} else if(ane::globalTime.GetTimeScale() != 1.0f) {
		ane::globalTime.SetTimeScale(1.0f);
	}

	ane::vec2 forward = ane::vec2(0, -1).Rotate(this->transform.rotation);
	AddForce(forward * this->speed * thrust);

	//this->transform.position += forward * speed * thrust * ane::globalTime.GetDeltaTime();
	this->transform.position.x = ane::Wrap(this->transform.position.x, static_cast<float> (ane::globalRenderer.GetWidth()));
	this->transform.position.y = ane::Wrap(this->transform.position.y, static_cast<float> (ane::globalRenderer.GetHeight()));
}

void Player::OnCollision(Actor* other) {
	if(dynamic_cast<Rocket*>(other) != nullptr && other->tag == "Enemy") {
		health -= 10;
	} else if(dynamic_cast<Bomber*>(other) != nullptr && other->tag == "Enemy") {
		health -= 20;
	}

	if(health <= 0) {
		if(!this->destroyed) {
			this->game->SetLives(this->game->GetLives() - 1);
		}
		dynamic_cast<SpaceGame*>(this->game)->SetState(SpaceGame::State::PlayerDeadStart);
		
		this->destroyed = true;
	}
}
 