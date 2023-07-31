#pragma once

#include "Renderer.h"
#include "Font.h"
#include "Core/Color.h"
#include <string>
#include <memory>

namespace ane {
	class Text {
		public:
			Text() = default;
			Text(std::shared_ptr<Font> font) {
				this->font = font;
			}
			~Text();

			void Create(Renderer& renderer, const std::string& text, const Color& color);
			void Draw(Renderer& renderer, int x, int y);

			friend class Font;
			friend class Renderer;

		private:
			std::shared_ptr<Font> font;
			struct SDL_Texture* texture = nullptr;
	};
}