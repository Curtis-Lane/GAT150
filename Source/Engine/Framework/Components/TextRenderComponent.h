#pragma once

#include "RenderComponent.h"

#include "Core/Math/Color.h"
#include "Renderer/Text.h"

namespace ane {
	class TextRenderComponent : public RenderComponent {
		public:
			CLASS_DECLARATION(TextRenderComponent);

			TextRenderComponent() = default;
			TextRenderComponent(const TextRenderComponent& other);

			bool Initialize() override;
			void Update(float deltaTime) override;
			void Draw(class Renderer& renderer) override;

			void SetText(const std::string& string);

		public:
			std::string text;
			std::string fontName;
			int fontSize = 0;
			Color color;

		private:
			bool changed = true;
			std::unique_ptr<Text> p_text;
	};
}