#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include "platform.h"
#include "pch.h"

namespace Core::Window {
	namespace Base {
		class IWindowBase {
		private:
			GLFWwindow* instance;
		protected:
			uInt32 __window_w;
			uInt32 __window_h;
			String __window_name;
			Byte _is_window_open;
		public:
			IWindowBase(String name, uInt32 w, uInt32 h);
			~IWindowBase();
		public:
			void updateWinInstances();
			void makeContextCurrent();
			sInt32 isWindowDestroyed();
		};
	};

};

#endif