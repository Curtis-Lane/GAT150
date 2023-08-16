#pragma once

#include "RenderComponent.h"

#include "Renderer/Model.h"

namespace ane {
	class ModelRenderComponent : public RenderComponent {
		public:
			CLASS_DECLARATION(ModelRenderComponent);

			bool Initialize() override;
			void Update(float deltaTime) override;
			void Draw(class Renderer& renderer) override;
			float GetRadius() override {return this->model->GetRadius();}

		public:
			std::string modelName;
			res_t<Model> model;
	};
}