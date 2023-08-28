#include "Box2DCollisionComponent.h"

#include "Box2DPhysicsComponent.h"
#include "SpriteRenderComponent.h"
#include "Framework/Actor.h"

namespace ane {
	CLASS_DEFINITION(Box2DCollisionComponent);

	bool Box2DCollisionComponent::Initialize() {
		auto component = this->owner->GetComponent<Box2DPhysicsComponent>();
		if(component != nullptr) {
			if(data.size.x == 0 && data.size.y == 0) {
				auto spriteComponent = this->owner->GetComponent<SpriteRenderComponent>();
				if(spriteComponent != nullptr) {
					data.size = Vector2(spriteComponent->source.w, spriteComponent->source.h);
				}
			}

			data.size = data.size * scaleOffset * this->owner->transform.scale;

			if(component->body->GetType() == b2_staticBody) {
				PhysicsSystem::Instance().SetCollisionBoxStatic(component->body, data, this->owner);
			} else {
				PhysicsSystem::Instance().SetCollisionBox(component->body, data, this->owner);
			}
		}

		return true;
	}

	void Box2DCollisionComponent::Update(float deltaTime) {
		//
	}

	void Box2DCollisionComponent::Read(const JSON_t& value) {
		READ_NAME_DATA(value, "size", data.size);
		READ_NAME_DATA(value, "density", data.density);
		READ_NAME_DATA(value, "friction", data.friction);
		READ_NAME_DATA(value, "restitution", data.restitution);
		READ_NAME_DATA(value, "isTrigger", data.isTrigger);

		READ_DATA(value, scaleOffset);
	}
}