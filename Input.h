#pragma once
#include "Game.h"
#include "GameObject.h"

namespace Game {
	namespace Input {
		GLenum getKey(GLenum key);

		template<class T> class BasicHoverable {
		public:
			virtual void onMouseHover() = 0; // you should implement it
			virtual void onMouseLeave() {};

		private:
			bool hovered = false;
			const Event::Iterator listener;

			void checkHover(double x, double y) {
				if (static_cast<T&>(*this).getShape().contains({ x, y })) {
					if (!hovered) {
						hovered = true;
						onMouseHover();
					}
				}
				else if (hovered) {
					hovered = false;
					onMouseLeave();
				}
			}

		public:

			bool isHovered() {
				return hovered;
			}

			BasicHoverable() : listener(Cursor::moved.connect([this] { checkHover(); })) {}
		};

		using Hoverable = BasicHoverable<GameObject>;
	}
}