#pragma once

#include "Object.h"

#include "Renderer/Renderer.h"
#include "Components/Component.h"

#include <memory>

namespace ane {
	class Actor : public Object {
		public:
			CLASS_DECLARATION(Actor)

			Actor() = default;
			Actor(const ane::Transform& transform) {this->transform = transform;}

			virtual bool Initialize() override;
			virtual void OnDestroy() override;

			virtual void Update(float deltaTime);
			virtual void Draw(ane::Renderer& renderer);

			void AddComponent(std::unique_ptr<Component> component);
			template<typename T>
			T* GetComponent();

			float GetRadius() {return 30.0f;}
			virtual void OnCollision(Actor* other) {;}

			class Scene* scene = nullptr;
			class Game* game = nullptr;

			friend class Scene;
			friend class Enemy;

		public:
			ane::Transform transform;
			std::string tag;
			float lifeSpan = -1.0f;
			bool destroyed = false;

		protected:
			std::vector<std::unique_ptr<Component>> components;
	};

	template<typename T>
	inline T* Actor::GetComponent() {
		for(std::unique_ptr<Component>& component : this->components) {
			T* result = dynamic_cast<T*>(component.get());
			if(result != nullptr) {
				return result;
			}
		}

		return nullptr;
	}
}