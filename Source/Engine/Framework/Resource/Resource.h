#pragma once

#include <string>

namespace ane {
	class Resource {
		public:
			virtual ~Resource() = default;

			virtual bool Create(std::string fileName, ...) = 0;
	};
}