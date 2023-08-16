#include "Actor.h"

#include "Components/RenderComponent.h"

namespace ane {
	CLASS_DEFINITION(Actor);

	bool Actor::Initialize() {
		for(auto& component : this->components) {
			component->Initialize();
		}

		return true;
	}

	void Actor::OnDestroy() {
		for(auto& component : this->components) {
			component->OnDestroy();
		}
	}

	void Actor::Update(float deltaTime) {
		if(this->lifeSpan != -1.0f) {
			this->lifeSpan -= deltaTime;

			if(this->lifeSpan <= 0.0f) {
				this->destroyed = true;
			}
		}

		for(auto& component : this->components) {
			component->Update(deltaTime);
		}
	}

	void Actor::Draw(ane::Renderer& renderer) {
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

	void Actor::Read(const rapidjson::Value& value) {
		Object::Read(value);

		READ_DATA(value, tag);
		READ_DATA(value, lifeSpan);

		if(HAS_DATA(value, transform)) {
			this->transform.Read(value);
		}

		if(HAS_DATA(value, components) && GET_DATA(value, components).IsArray()) {
			for(auto& componentValue : GET_DATA(value, components).GetArray()) {
				std::string type;
				READ_DATA(componentValue, type);

				auto component = CREATE_CLASS_BASE(Component, type);
				component->Read(componentValue);
				this->AddComponent(std::move(component));
			}
		}
	}
}
