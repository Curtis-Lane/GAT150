#pragma once

#include "RenderComponent.h"

#include "Renderer/Texture.h"

#include "Framework/Factory.h"

namespace ane {
	class SpriteRenderComponent : public RenderComponent {
		public:
			CLASS_DECLARATION(SpriteRenderComponent);

			void Update(float deltaTime) override;
			void Draw(class Renderer& renderer) override;
			float GetRadius() override {return this->texture->GetSize().Length() * 0.5f;}

		public:
			res_t<Texture> texture;
	};
}