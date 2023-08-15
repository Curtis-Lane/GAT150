#include "ModelRenderComponent.h"

#include "Framework/Actor.h"

namespace ane {
	CLASS_DEFINITION(ModelRenderComponent);

	void ModelRenderComponent::Update(float deltaTime) {
		//
	}

	void ModelRenderComponent::Draw(Renderer& renderer) {
		this->model->Draw(renderer, this->owner->transform);
	}
}
