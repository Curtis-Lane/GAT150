#include "Actor.h"

#include "Components/RenderComponent.h"

namespace ane {
	CLASS_DEFINITION(Actor);

	Actor::Actor(const Actor& other) {
		this->name = other.name;
		this->tag = other.tag;
		this->lifeSpan = other.lifeSpan;
		this->transform = other.transform;
		this->persistent = other.persistent;
		this->scene = other.scene;
		this->game = other.game;

		for(auto& component : other.components) {
			auto cloneComponent = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
			this->AddComponent(std::move(cloneComponent));
		}
	}

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
		READ_DATA(value, persistent);
		READ_DATA(value, prototype);

		if(HAS_DATA(value, transform)) {
			this->transform.Read(GET_DATA(value, transform));
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
