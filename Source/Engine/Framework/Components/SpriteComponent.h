#pragma once

#include "RenderComponent.h"

#include "Renderer/Texture.h"

namespace ane {
	class SpriteComponent : public RenderComponent {
		public:
			void Update(float deltaTime) override;
			void Draw(class Renderer& renderer) override;

		public:
			res_t<Texture> texture;
	};
}