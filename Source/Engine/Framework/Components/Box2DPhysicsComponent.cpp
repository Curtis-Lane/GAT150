#include "Box2DPhysicsComponent.h"

#include "Framework/Actor.h"

namespace ane {
	CLASS_DEFINITION(Box2DPhysicsComponent);

	bool Box2DPhysicsComponent::Initialize() {
		this->body = PhysicsSystem::Instance().CreateBody(this->owner->transform.position, this->owner->transform.rotation, data);
		this->body->SetGravityScale(data.gravityScale);
		this->body->SetLinearDamping(data.damping);
		this->body->SetAngularDamping(data.angularDamping);

		return true;
	}

	void Box2DPhysicsComponent::OnDestroy() {
		if(this->body != nullptr) {
			this->body->SetEnabled(false);
			PhysicsSystem::Instance().DestroyBody(this->body);
		}
	}

	void Box2DPhysicsComponent::Update(float dt) {
		Vector2 position = B2VEC2_TO_VEC2(this->body->GetPosition());
		this->owner->transform.position = PhysicsSystem::Instance().WorldToScreen(position);
		this->owner->transform.rotation = this->body->GetAngle();
		velocity = B2VEC2_TO_VEC2(this->body->GetLinearVelocity());
	}

	void Box2DPhysicsComponent::ApplyForce(const Vector2& force) {
		this->body->ApplyForceToCenter(VEC2_TO_B2VEC2(force), true);
	}

	void Box2DPhysicsComponent::ApplyTorque(float torque) {
		this->body->ApplyTorque(torque, true);
	}

	void Box2DPhysicsComponent::SetVelocity(const Vector2& velocity) {
		this->body->SetLinearVelocity(VEC2_TO_B2VEC2(velocity));
	}

	void Box2DPhysicsComponent::Read(const JSON_t& value) {
		READ_NAME_DATA(value, "damping", data.damping);
		READ_NAME_DATA(value, "angularDamping", data.angularDamping);
		READ_NAME_DATA(value, "gravityScale", data.gravityScale);
		READ_NAME_DATA(value, "constrainAngle", data.constrainAngle);
		READ_NAME_DATA(value, "isDynamic", data.isDynamic);
	}
}