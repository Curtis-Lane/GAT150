#include "Text.h"

#include <SDL2-2.28.0/include/SDL_ttf.h>

#include "Renderer.h"

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

	void Text::Draw(Renderer& renderer, const Transform& transform) {
		int width, height;
		SDL_QueryTexture(this->texture, nullptr, nullptr, &width, &height);

		Matrix3x3 matrix = transform.GetMatrix();
		Vector2 position = matrix.GetTranslation();
		Vector2 size = Vector2(width, height) * matrix.GetScale();

		SDL_Rect dest;
		dest.x = static_cast<int>(position.x - (size.x * 0.5f));
		dest.y = static_cast<int>(position.y - (size.y * 0.5f));
		dest.w = static_cast<int>(size.x);
		dest.h = static_cast<int>(size.y);

		// https://wiki.libsdl.org/SDL2/SDL_RenderCopyEx
		SDL_RenderCopyEx(renderer.renderer, this->texture, nullptr, &dest, RadiansToDegrees(matrix.GetRotation()), nullptr, SDL_FLIP_NONE);
	}
}