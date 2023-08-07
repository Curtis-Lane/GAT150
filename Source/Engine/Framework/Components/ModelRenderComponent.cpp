#include "ModelRenderComponent.h"

#include "Framework/Actor.h"

namespace ane {
	void ModelRenderComponent::Update(float deltaTime) {
		//
	}

	void ModelRenderComponent::Draw(Renderer& renderer) {
		this->model->Draw(renderer, this->owner->transform);
	}
}
