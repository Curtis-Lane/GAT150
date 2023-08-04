#include "SpriteComponent.h"

#include "Renderer/Renderer.h"
#include "Framework/Actor.h"

namespace ane {
	void SpriteComponent::Update(float deltaTime) {
		//
	}

	void SpriteComponent::Draw(Renderer& renderer) {
		renderer.DrawTexture(this->texture.get(), this->owner->transform.position.x, this->owner->transform.position.y, RadiansToDegrees(this->owner->transform.rotation));
	}
}