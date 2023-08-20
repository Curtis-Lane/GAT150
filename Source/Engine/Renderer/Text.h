#pragma once

#include <string>
#include <memory>

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

			void Create(class Renderer& renderer, const std::string& text, const class Color& color);
			void Draw(class Renderer& renderer, int x, int y);
			void Draw(class Renderer& renderer, const class Transform& transform);

			friend class Font;
			friend class Renderer;

		private:
			std::shared_ptr<Font> font;
			SDL_Texture* texture = nullptr;
	};
}