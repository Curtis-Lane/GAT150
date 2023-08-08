#pragma once

#include <string>
#include <memory>

#include "Core/Math/Color.h"
#include "Font.h"

struct SDL_Texture;

namespace ane {
	class Text {
		public:
			Text() = default;
			Text(std::shared_ptr<Font> font) {
				this->font = font;
			}
			~Text();

			void Create(class Renderer& renderer, const std::string& text, const Color& color);
			void Draw(class Renderer& renderer, int x, int y);

			friend class Font;
			friend class Renderer;

		private:
			std::shared_ptr<Font> font;
			SDL_Texture* texture = nullptr;
	};
}