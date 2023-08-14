#include "SpriteRenderComponent.h"

#include "Renderer/Renderer.h"
#include "Framework/Actor.h"

namespace ane {
	void SpriteRenderComponent::Update(float deltaTime) {
		//
	}

	void SpriteRenderComponent::Draw(Renderer& renderer) {
		renderer.DrawTexture(this->texture.get(), this->owner->transform);
	}
}