#include "SpriteRenderComponent.h"

#include "Framework/Resource/ResourceManager.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"

namespace ane {
	CLASS_DEFINITION(SpriteRenderComponent);

	bool SpriteRenderComponent::Initialize() {
		this->texture = GET_RESOURCE(Texture, textureName, globalRenderer);

		return true;
	}

	void SpriteRenderComponent::Update(float deltaTime) {
		//
	}

	void SpriteRenderComponent::Draw(Renderer& renderer) {
		renderer.DrawTexture(this->texture.get(), this->owner->transform);
	}

	void SpriteRenderComponent::Read(const JSON_t& value) {
		READ_DATA(value, textureName);
	}
}