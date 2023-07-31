#include "Rocket.h"

void Rocket::Update(float deltaTime) {
	Actor::Update(deltaTime);

	ane::vec2 forward = ane::vec2(0, -1).Rotate(this->transform.rotation);
	this->transform.position += forward * speed * ane::globalTime.GetDeltaTime();
	this->transform.position.x = ane::Wrap(this->transform.position.x, static_cast<float> (ane::globalRenderer.GetWidth()));
	this->transform.position.y = ane::Wrap(this->transform.position.y, static_cast<float> (ane::globalRenderer.GetHeight()));
}

void Rocket::OnCollision(Actor* other) {
	if(other->tag != this->tag) {
		this->destroyed = true;
	}
}
