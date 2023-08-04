#include "Font.h"

#include "SDL2-2.28.0/include/SDL_ttf.h"
#include "Core/Logger.h"

namespace ane {
	Font::Font(const std::string& fileName, int fontSize) {
		Load(fileName, fontSize);
	}

	Font::~Font() {
		if(this->ttfFont != NULL) {
			TTF_CloseFont(this->ttfFont);
		}
	}

	bool Font::Create(std::string fileName, ...) {
		va_list args;

		va_start(args, fileName);

		int fontSize = va_arg(args, int);

		va_end(args);

		return Load(fileName, fontSize);
	}

	bool Font::Load(const std::string& fileName, int fontSize) {
		this->ttfFont = TTF_OpenFont(fileName.c_str(), fontSize);
		if(this->ttfFont == nullptr) {
			WARNING_LOG("Failed to open font: " << fileName);
			return false;
		} else {
			return true;
		}
	}
}