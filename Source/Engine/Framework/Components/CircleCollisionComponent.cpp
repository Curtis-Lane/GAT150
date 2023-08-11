#include "CircleCollisionComponent.h"

#include "Framework/Actor.h"

namespace ane {
    void CircleCollisionComponent::Update(float deltaTime) {
        //
    }

    bool CircleCollisionComponent::CheckCollision(CollisionComponent* collision) {
        float distance = this->owner->transform.position.Distance(collision->owner->transform.position);
        float radius = this->radius + collision->radius;

        return (distance <= radius);
    }
}