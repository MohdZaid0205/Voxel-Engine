#include "window.h"

Core::Window::Base::IWindowBase::IWindowBase(String name, uInt32 w, uInt32 h){
	__window_w = w;
	__window_h = h;
	__window_name = name;
	_is_window_open = true;
	instance = glfwCreateWindow(w, h, name.c_str(), NULL, NULL);
}

Core::Window::Base::IWindowBase::~IWindowBase(){
	if (_is_window_open) {
		glfwDestroyWindow(instance);
	}
}
