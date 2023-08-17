#include "Rocket.h"

#include "Framework/Components/CollisionComponent.h"
#include "Framework/Components/RenderComponent.h"

bool Rocket::Initialize() {
	ane::CollisionComponent* collisionComponent = this->GetComponent<ane::CollisionComponent>();
	if(collisionComponent != nullptr) {
		ane::RenderComponent* renderComponent = this->GetComponent<ane::RenderComponent>();
		if(renderComponent != nullptr) {
			float scale = this->transform.scale;
			collisionComponent->radius = renderComponent->GetRadius() * scale;
		}
	}

	return true;
}

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

void Rocket::Read(const ane::JSON_t& value) {
	READ_DATA(value, speed);
}
