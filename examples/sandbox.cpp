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

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.5f, 1.0f);\n"
"}\0";

int main(int argc, char** argv){
    
    glfwInit(); // initialise and instruct versions.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* mainWin;    // make main window 
    GLFWwindow* sideWin;    // make side window

    mainWin = glfwCreateWindow(MAIN_WIN_W, MAIN_WIN_H, MAIN_WIN_T, NULL, NULL);
    sideWin = glfwCreateWindow(SIDE_WIN_W, SIDE_WIN_H, SIDE_WIN_T, NULL, NULL);

    if (mainWin == NULL || sideWin == NULL) {
        Console::Error<Console::HIG>("Falied to initalise window "_D, "mian="_B, mainWin, "side="_B, sideWin);
        return -1;
    }

    GLboolean anyWindowIsOpen = true;
    GLboolean mainWindowIsOpen = true;
    GLboolean sideWindowIsOpen = true;

    // load vertices for triangles on respective screens
    GLfloat mainVerts[] = {
         0.0f,  0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f,
         0.5f, -0.5f,  0.0f,
    };
    
    GLfloat sideVerts[] = {
        -0.5f,  0.5f,  0.0f,
         0.5f,  0.5f,  0.0f,
         0.0f, -0.5f,  0.0f,
    };

    glfwMakeContextCurrent(mainWin);
    gladLoadGL();
    // address that we need memory and tell to gpu, waitr for it to assign you id.
    // id is important and it keeps track of where in gpu mem out data is stored.
    GLuint mainVertBufferObject;
    glGenBuffers(1, &mainVertBufferObject);
    GLuint mainVertAttributeObject;
    glGenVertexArrays(1, &mainVertAttributeObject);
    // tell it that i am taking about data with this id.
    glBindVertexArray(mainVertAttributeObject);
    glBindBuffer(GL_ARRAY_BUFFER, mainVertBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mainVerts), mainVerts, GL_STATIC_DRAW);
    

    glfwMakeContextCurrent(sideWin);
    gladLoadGL();
    // dp some same shit for side window and manage it
    GLuint sideVertBufferObject;
    glGenBuffers(1, &sideVertBufferObject);
    GLuint sideVertAttributeObject;
    glGenVertexArrays(1, &sideVertAttributeObject);
    // switch id andd bind to tell what data to work on now.
    glBindVertexArray(sideVertAttributeObject);
    glBindBuffer(GL_ARRAY_BUFFER, sideVertBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sideVerts), sideVerts, GL_STATIC_DRAW);

    glfwMakeContextCurrent(mainWin);
    // compike the vertex shader (a boilerplate maybe!).
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint vertShaderCompiled;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertShaderCompiled);
    if (!vertShaderCompiled){
        GLchar vertShaderException[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, vertShaderException);
        Console::Error<Console::HIG>("Failed to compile vertex shader due to :"_D, vertShaderException);
    }
    else {
        Console::Debug<Console::HIG>("Success in compiling vertex shader"_D);
    }

    // compike the fragment shader (a boilerplate maybe!).
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLint fragShaderCompiled;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragShaderCompiled);
    if (!fragShaderCompiled) {
        GLchar fragShaderException[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, fragShaderException);
        Console::Error<Console::HIG>("Failed to compile fragment shader due to :"_D, fragShaderException);
    }
    else {
        Console::Debug<Console::HIG>("Success in compiling fragment shader"_D);
    }

    // create a program and attch both the shaders to this  program.
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint shaderProgramCreated;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &shaderProgramCreated);
    if (!shaderProgramCreated) {
        GLchar shaderProgramException[512];
        glGetProgramInfoLog(shaderProgramCreated, 512, NULL, shaderProgramException);
        Console::Error<Console::HIG>("Failed to link both shaders due to :"_D, shaderProgramException);
    }
    else {
        Console::Debug<Console::HIG>("Success in linking fragment shader with vertex shader"_D);
    }

    // specify that we will use this program
    glUseProgram(shaderProgram);

    glfwMakeContextCurrent(mainWin);
    gladLoadGL();
    glBindVertexArray(mainVertAttributeObject);
    glBindBuffer(GL_ARRAY_BUFFER, mainVertBufferObject);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glfwMakeContextCurrent(sideWin);
    gladLoadGL();
    glBindVertexArray(sideVertAttributeObject);
    glBindBuffer(GL_ARRAY_BUFFER, sideVertBufferObject);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

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
                glBindVertexArray(mainVertAttributeObject);
                glDrawArrays(GL_TRIANGLES, 0, 3);
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
                glBindVertexArray(sideVertAttributeObject);
                glDrawArrays(GL_TRIANGLES, 0, 3);
                glfwSwapBuffers(sideWin);
            }
        }

        anyWindowIsOpen = mainWindowIsOpen | sideWindowIsOpen;

        glfwPollEvents();
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glfwTerminate();
    return 0;
}