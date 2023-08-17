#include "CircleCollisionComponent.h"

#include "Framework/Actor.h"

namespace ane {
    CLASS_DEFINITION(CircleCollisionComponent);

    void CircleCollisionComponent::Update(float deltaTime) {
        //
    }

    bool CircleCollisionComponent::CheckCollision(CollisionComponent* collision) {
        float distance = this->owner->transform.position.Distance(collision->owner->transform.position);
        float radius = this->radius + collision->radius;

        return (distance <= radius);
    }

    void CircleCollisionComponent::Read(const JSON_t& value) {
        //
    }
}