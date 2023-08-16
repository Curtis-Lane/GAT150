#include "ModelRenderComponent.h"

#include "Framework/Resource/ResourceManager.h"
#include "Framework/Actor.h"

namespace ane {
	CLASS_DEFINITION(ModelRenderComponent);

	bool ModelRenderComponent::Initialize() {
		this->model = GET_RESOURCE(Model, modelName);

		return true;
	}

	void ModelRenderComponent::Update(float deltaTime) {
		//
	}

	void ModelRenderComponent::Draw(Renderer& renderer) {
		this->model->Draw(renderer, this->owner->transform);
	}

	void ModelRenderComponent::Read(const JSON_t& value) {
		READ_DATA(value, modelName);
	}
}
