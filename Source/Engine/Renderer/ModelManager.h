#pragma once

#include "Model.h"

#include <string>
#include <map>
#include <memory>

namespace ane {
	class ModelManager {
		public:
			std::shared_ptr<Model> Get(const std::string& fileName);

		private:
			std::map<std::string, std::shared_ptr<Model>> models;
	};

	extern ModelManager globalModelManager;
}