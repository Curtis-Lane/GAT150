#include "ModelManager.h"

namespace ane {
	ModelManager globalModelManager;

	std::shared_ptr<Model> ModelManager::Get(const std::string& fileName) {
		if(this->models.find(fileName) == this->models.end()) {
			std::shared_ptr<Model> model = std::make_shared<Model>();
			model->Load(fileName);

			this->models[fileName] = model;
		}

		return this->models[fileName];
	}
}