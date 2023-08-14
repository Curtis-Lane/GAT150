#include "Texture.h"

#include "SDL2-2.28.0/include/SDL_image.h"
#include "Core/Logger.h"
#include "Renderer.h"

namespace ane {
	Texture::~Texture() {
		if(this->texture != nullptr) {
			SDL_DestroyTexture(this->texture);
		}
	}

	bool Texture::Create(std::string fileName, ...) {
		va_list args;

		va_start(args, fileName);

		Renderer& renderer = va_arg(args, Renderer);

		va_end(args);

		return Load(fileName, renderer);
	}

	bool Texture::Load(const std::string& fileName, Renderer& renderer) {
		SDL_Surface* surface = IMG_Load(fileName.c_str());
		if(surface == nullptr) {
			WARNING_LOG("Image not found: " << fileName.c_str());
			return false;
		}

		this->texture = SDL_CreateTextureFromSurface(renderer.renderer, surface);
		SDL_FreeSurface(surface);
		if(this->texture == nullptr) {
			WARNING_LOG("Error in creating texture");
			return false;
		}

		return true;
	}

	Vector2 Texture::GetSize() {
		ASSERT_LOG((this->texture != nullptr), "Texture is null pointer");
		SDL_Point point;
		// https://wiki.libsdl.org/SDL2/SDL_QueryTexture
		SDL_QueryTexture(this->texture, NULL, NULL, &point.x, &point.y);

		return Vector2(point.x, point.y);
	}
}