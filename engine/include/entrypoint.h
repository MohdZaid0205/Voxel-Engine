#ifndef VOXEL_ENGINE_ENTRYPOINT_H
#define VOXEL_ENGINE_ENTRYPOINT_H

#include "common.h"
#include "glad/glad.h"
#include "glfw/glfw3.h"
int dummy_main(int argc,char** argv);

int main(int argc,char** argv){


	Common::Console::Info<Common::Console::HIG>("invoking glfw");
	glfwInit(); // initialise and instruct versions.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	Common::Console::Log("Engine has started executing."_D);

	int result = dummy_main(argc,argv);
	Common::Console::Log("Engine has stopped running and returend with exit code."_D,result);
	return result;
}

#define main dummy_main

#endif