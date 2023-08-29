#include "SpriteRenderComponent.h"

#include "Framework/Resource/ResourceManager.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"

namespace ane {
	CLASS_DEFINITION(SpriteRenderComponent);

	bool SpriteRenderComponent::Initialize() {
		if(!textureName.empty()) {
			this->texture = GET_RESOURCE(Texture, textureName, globalRenderer);
		}

		if(this->source.w == 0 && this->source.h == 0) {
			if(this->texture != nullptr) {
				this->source.x = 0;
				this->source.y = 0;
				this->source.w = static_cast<int>(this->texture->GetSize().x);
				this->source.h = static_cast<int>(this->texture->GetSize().y);
			}
		}

		return true;
	}

	void SpriteRenderComponent::Update(float deltaTime) {
		//
	}

	void SpriteRenderComponent::Draw(Renderer& renderer) {
		renderer.DrawTexture(this->texture.get(), this->source, this->owner->transform, this->origin, this->flipH);
	}

	void SpriteRenderComponent::Read(const JSON_t& value) {
		READ_DATA(value, source);
		READ_DATA(value, flipH);
		READ_DATA(value, origin);
		READ_DATA(value, textureName);
	}
}