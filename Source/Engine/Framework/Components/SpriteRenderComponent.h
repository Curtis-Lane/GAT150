#pragma once

#include "RenderComponent.h"

#include "Renderer/Texture.h"
#include "Core/Math/Rect.h"

#include "Framework/Factory.h"

namespace ane {
	class SpriteRenderComponent : public RenderComponent {
		public:
			CLASS_DECLARATION(SpriteRenderComponent);

			bool Initialize() override;
			void Update(float deltaTime) override;
			void Draw(class Renderer& renderer) override;

		public:
			Rect source;
			bool flipH = false;
			Vector2 origin = Vector2(0.5f, 0.5f);

			std::string textureName;
			res_t<Texture> texture;
	};
}