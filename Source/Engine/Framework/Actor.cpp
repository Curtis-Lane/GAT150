#include "Actor.h"

#include "Components/RenderComponent.h"

namespace ane {
	void Actor::Update(float deltaTime) {
		if(this->lifeSpan != -1.0f) {
			this->lifeSpan -= deltaTime;

			if(this->lifeSpan <= 0.0f) {
				this->destroyed = true;
			}
		}

		this->transform.position += this->velocity * deltaTime;
		this->velocity *= std::pow(1.0f - this->damping, deltaTime);
	}

	void Actor::Draw(ane::Renderer& renderer) {
		//this->model->Draw(renderer, this->transform);
		for(auto& component : this->components) {
			RenderComponent* renderComponent = dynamic_cast<RenderComponent*>(component.get());
			if(renderComponent != nullptr) {
				renderComponent->Draw(renderer);
			}
		}
	}

	void Actor::AddComponent(std::unique_ptr<Component> component) {
		component->owner = this;
		this->components.push_back(std::move(component));
	}
}
