#pragma once

#include "MathUtils.h"

#include <cstdint>
#include <iostream>
#include <string>

namespace ane {
	class Color {
		public:
			float r, g, b, a;

		public:
			Color() {
				r, b, g, a = 0;
			}
			Color(float r, float g, float b, float a = 1.0f) {
				this->r = r;
				this->g = g;
				this->b = b;
				this->a = a;
			}

			static uint8_t ToInt(float color) {return static_cast<uint8_t>(Clamp(color, 0.0f, 1.0f) * 255);}
	};

	inline std::istream& operator >> (std::istream& stream, Color& color) {
		std::string line;
		std::getline(stream, line);

		// line = { ##, ##, ## }

		// Red
		std::string str = line.substr(line.find('{') + 2, line.find(',') - line.find('{') - 2);
		color.r = std::stof(str);


		// Green
		line = line.substr(line.find(',') + 1);
		str = line.substr(1, line.find(',') - 1);
		color.g = std::stof(str);

		// Blue
		str = line.substr(line.find(',') + 2, line.find('}') - 5);
		color.b = std::stof(str);

		// Alpha
		color.a = 1.0f;

		return stream;
	}
}