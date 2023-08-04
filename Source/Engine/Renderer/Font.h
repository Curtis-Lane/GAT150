#pragma once

#include <string>

#include "Framework/Resource/Resource.h"

struct _TTF_Font;

namespace ane {
	class Font : public Resource {
		public:
			Font() = default;
			Font(const std::string& fileName, int fontSize);
			~Font();

			virtual bool Create(std::string fileName, ...) override;
			bool Load(const std::string& fileName, int fontSize);

			friend class Text;

		private:
			_TTF_Font* ttfFont = nullptr;
	};
}