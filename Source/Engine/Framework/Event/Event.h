#pragma once

#include <variant>
#include <string>

namespace ane {
	class Event {
		public:
			using id_t = std::string;
			using data_t = std::variant<int, bool, float, std::string>;

		public:
			Event() = default;
			Event(const id_t& id, data_t data) {this->id = id; this->data = data;}

		public:
			id_t id;
			data_t data;
	};
}