#include "Font.h"

#include "SDL2-2.28.0/include/SDL_ttf.h"

namespace ane {
	Font::Font(const std::string& fileName, int fontSize) {
		Load(fileName, fontSize);
	}

	Font::~Font() {
		if(this->ttfFont != NULL) {
			TTF_CloseFont(this->ttfFont);
		}
	}

	void Font::Load(const std::string& fileName, int fontSize) {
		this->ttfFont = TTF_OpenFont(fileName.c_str(), fontSize);
	}
}