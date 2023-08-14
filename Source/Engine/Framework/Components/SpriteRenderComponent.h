#pragma once

#include "RenderComponent.h"

#include "Renderer/Texture.h"

namespace ane {
	class SpriteRenderComponent : public RenderComponent {
		public:
			void Update(float deltaTime) override;
			void Draw(class Renderer& renderer) override;
			float GetRadius() override {return this->texture->GetSize().Length() * 0.5f;}

		public:
			res_t<Texture> texture;
	};
}