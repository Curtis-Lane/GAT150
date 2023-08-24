#include "Rocket.h"

#include "Framework/Components/CollisionComponent.h"
#include "Framework/Components/RenderComponent.h"

CLASS_DEFINITION(Rocket);

bool Rocket::Initialize() {
	Actor::Initialize();

	// Cache off
	this->physicsComponent = GetComponent<ane::PhysicsComponent>();

	ane::CollisionComponent* collisionComponent = this->GetComponent<ane::CollisionComponent>();
	if(collisionComponent != nullptr) {
		//
	}

	return true;
}

void Rocket::Update(float deltaTime) {
	Actor::Update(deltaTime);

	ane::vec2 forward = ane::vec2(0, -1).Rotate(this->transform.rotation);
	this->physicsComponent->SetVelocity(forward * speed);

	this->transform.position.x = ane::Wrap(this->transform.position.x, static_cast<float>(ane::globalRenderer.GetWidth()));
	this->transform.position.y = ane::Wrap(this->transform.position.y, static_cast<float>(ane::globalRenderer.GetHeight()));
}

void Rocket::OnCollisionEnter(Actor* other) {
	if(other->tag != this->tag) {
		this->destroyed = true;
	}
}

void Rocket::Read(const ane::JSON_t& value) {
	Actor::Read(value);

	READ_DATA(value, speed);
}
