#include "Model.h"

#include <sstream>

#include "Core/FileIO.h"
#include "Renderer.h"

namespace ane {
	bool Model::Create(std::string fileName, ...) {
		return Load(fileName);
	}

	bool Model::Load(const std::string& filename) {
		std::string buffer;
		ane::readFile(filename, buffer);

		std::istringstream stream(buffer);

		stream >> this->color;

		std::string line;
		std::getline(stream, line);

		int numPoints = std::stoi(line);
		for(int i = 0; i < numPoints; i++) {
			vec2 point;

			stream >> point;

			this->points.push_back(point);
		}

		return true;
	}

	void Model::Draw(Renderer& renderer, const vec2& position, float rotation, float scale) {
		if(points.empty()) {
			return;
		}

		renderer.SetColor(Color::ToInt(this->color.r), Color::ToInt(this->color.g), Color::ToInt(this->color.b), Color::ToInt(this->color.a));

		for(size_t i = 0; i < (points.size() - 1); i++) {
			vec2 p1 = (points[i] * scale).Rotate(rotation) + position;
			vec2 p2 = (points[i + 1] * scale).Rotate(rotation) + position;

			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	void Model::Draw(Renderer& renderer, const Transform& transform) {
		if(points.empty()) {
			return;
		}

		Matrix3x3 matrix = transform.GetMatrix();

		renderer.SetColor(Color::ToInt(this->color.r), Color::ToInt(this->color.g), Color::ToInt(this->color.b), Color::ToInt(this->color.a));

		for(size_t i = 0; i < (points.size() - 1); i++) {
			Vector2 p1 = matrix * points[i];
			Vector2 p2 = matrix * points[i + 1];

			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	float Model::GetRadius() {
		if(this->radius == 0.0f) {
			for(Vector2 point : this->points) {
				float length = point.Length();
				this->radius = Max(this->radius, length);
			}
		}

		return this->radius;
	}
}