#include <iostream>
#include "engine.h"

#include "glad/glad.h"
#include "glfw/glfw3.h"

using namespace Core;

#define MAIN_WIN_H 600
#define MAIN_WIN_W 800
#define MAIN_WIN_T "MAIN"

#define SIDE_WIN_H 400
#define SIDE_WIN_W 600
#define SIDE_WIN_T "SIDE"


int main(int argc, char** argv){
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* mainWin;
    GLFWwindow* sideWin;

    mainWin = glfwCreateWindow(MAIN_WIN_W, MAIN_WIN_H, MAIN_WIN_T, NULL, NULL);
    sideWin = glfwCreateWindow(SIDE_WIN_W, SIDE_WIN_H, SIDE_WIN_T, NULL, NULL);

    if (mainWin == NULL || sideWin == NULL) {
        Console::Error<Console::HIG>("Falied to initalise window "_D, "mian="_B, mainWin, "side="_B, sideWin);
        return -1;
    }

    bool anyWindowIsOpen = true;
    bool mainWindowIsOpen = true;
    bool sideWindowIsOpen = true;
    
    glfwMakeContextCurrent(mainWin);
    gladLoadGL();

    while (anyWindowIsOpen) {
        
        if (mainWindowIsOpen) {
            if (glfwWindowShouldClose(mainWin)) {
                mainWindowIsOpen = false;
                glfwDestroyWindow(mainWin);
                Console::Log("Destroyed main Window."_D);
                continue;
            }
            glfwMakeContextCurrent(mainWin);
            
            {
                glViewport(0, 0, MAIN_WIN_W, MAIN_WIN_H);
                glClearColor(0.5, 0.5, 1, 1);
                glClear(GL_COLOR_BUFFER_BIT);
                glfwSwapBuffers(mainWin);
            }
        }
        
        if (sideWindowIsOpen) {
            if (glfwWindowShouldClose(sideWin)) {
                sideWindowIsOpen = false;
                glfwDestroyWindow(sideWin);
                Console::Log("Destroyed side Window."_D);
                continue;
            }
            glfwMakeContextCurrent(sideWin);
            
            {
                glViewport(0, 0, SIDE_WIN_W, SIDE_WIN_H);
                glClearColor(0.5, 1, 0.5, 1);
                glClear(GL_COLOR_BUFFER_BIT);
                glfwSwapBuffers(sideWin);
            }
        }

        anyWindowIsOpen = mainWindowIsOpen || sideWindowIsOpen;

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}