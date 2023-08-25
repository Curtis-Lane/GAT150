#pragma once

namespace ane {
	class Rect {
		public:
			int x, y, w, h;

		public:
			Rect() {x, y, w, h = 0;}
			Rect(int x, int y, int w, int h) {
				this->x = x;
				this->y = y;
				this->w = w;
				this->h = h;
			}

			int  operator [] (size_t index) const {return (&x)[index];}
			int& operator [] (size_t index) {return (&x)[index];}
	};
}