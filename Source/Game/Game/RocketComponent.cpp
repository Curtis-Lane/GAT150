#include "RocketComponent.h"

#include "Framework/Components/CollisionComponent.h"
#include "Framework/Components/RenderComponent.h"
#include "Framework/Actor.h"

namespace ane {
	bool RocketComponent::Initialize() {
		ane::CollisionComponent* collisionComponent = this->owner->GetComponent<ane::CollisionComponent>();
		if(collisionComponent != nullptr) {
			ane::RenderComponent* renderComponent = this->owner->GetComponent<ane::RenderComponent>();
			if(renderComponent != nullptr) {
				float scale = this->owner->transform.scale;
				collisionComponent->radius = renderComponent->GetRadius() * scale;
			}
		}

		return true;
	}

	void RocketComponent::Update(float deltaTime) {
		ane::vec2 forward = ane::vec2(0, -1).Rotate(this->owner->transform.rotation);
		this->owner->transform.position += forward * speed * ane::globalTime.GetDeltaTime();
		this->owner->transform.position.x = ane::Wrap(this->owner->transform.position.x, static_cast<float> (ane::globalRenderer.GetWidth()));
		this->owner->transform.position.y = ane::Wrap(this->owner->transform.position.y, static_cast<float> (ane::globalRenderer.GetHeight()));
	}

	void RocketComponent::OnCollision(Actor* other) {
		if(other->tag != this->owner->tag) {
			this->owner->destroyed = true;
		}
	}

	void RocketComponent::Read(const JSON_t& value) {
		READ_DATA(value, speed);
	}
}