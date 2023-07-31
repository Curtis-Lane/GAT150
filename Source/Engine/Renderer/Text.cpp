#include "Text.h"

#include "Font.h"
#include "SDL2-2.28.0/include/SDL_ttf.h"

namespace ane {
	Text::~Text() {
		if(this->texture != nullptr) {
			SDL_DestroyTexture(this->texture);
		}
	}

	void Text::Create(Renderer& renderer, const std::string& text, const Color& color) {
		if(this->texture != nullptr) {
			SDL_DestroyTexture(this->texture);
		}

		SDL_Color c{Color::ToInt(color.r), Color::ToInt(color.g), Color::ToInt(color.b), Color::ToInt(color.a)};
		SDL_Surface* surface = TTF_RenderText_Solid(this->font->ttfFont, text.c_str(), c);
		this->texture = SDL_CreateTextureFromSurface(renderer.renderer, surface);
		SDL_FreeSurface(surface);
	}

	void Text::Draw(Renderer& renderer, int x, int y) {
		int width, height;
		SDL_QueryTexture(this->texture, nullptr, nullptr, &width, &height);

		SDL_Rect rect{x, y, width, height};
		SDL_RenderCopy(renderer.renderer, this->texture, NULL, &rect);
	}
}