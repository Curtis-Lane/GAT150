#include "Model.h"
#include "Core/FileIO.h"
#include <sstream>

namespace ane {
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
		Draw(renderer, transform.position, transform.rotation, transform.scale);
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