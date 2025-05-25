#include "shaders.h"

Core::Shaders::Base::IShaderBase::IShaderBase(String src, GLenum shaderType){
    __shader_source = src.c_str();
    __shader_identity = glCreateShader(shaderType);
    __shader_compiled = false;
    glShaderSource(__shader_identity, 1, &__shader_source, NULL);
}

Core::Shaders::Base::IShaderBase::~IShaderBase(){
    if (__shader_compiled) {
        destroy();
    }
}

void Core::Shaders::Base::IShaderBase::compile() {
    Core::Console::Error<Console::HIG>(typeid(this).name(), "does not impliment"_D, "compile"_H, "method properly."_D);
}

void Core::Shaders::Base::IShaderBase::destroy() {
    Core::Console::Error<Console::HIG>(typeid(this).name(), "does not impliment"_D, "destroy"_H, "method properly."_D);
}

Core::uInt32 Core::Shaders::Base::IShaderBase::getIdentity(){
    return __shader_identity;
}

Core::sInt32 Core::Shaders::Base::IShaderBase::getCompiled(){
    return __shader_compiled;
}

void Core::Shaders::VertexShader::compile(){
    glCompileShader(__shader_identity);
    glGetShaderiv(__shader_identity, GL_COMPILE_STATUS, &__shader_compiled);
    if (!__shader_compiled) {
        GLchar vertShaderException[512];
        glGetShaderInfoLog(__shader_identity, 512, NULL, vertShaderException);
        Core::Console::Error<Console::HIG>("Failed to compile vertex shader due to :"_D, vertShaderException);
    }
    else {
        Core::Console::Debug<Console::MED>("Success in compiling vertex shader"_D);
    }
}

void Core::Shaders::VertexShader::destroy(){
    glDeleteShader(__shader_identity);
    __shader_compiled = 0;
}

void Core::Shaders::FragmentShader::compile(){
    glCompileShader(__shader_identity);
    glGetShaderiv(__shader_identity, GL_COMPILE_STATUS, &__shader_compiled);
    if (!__shader_compiled) {
        GLchar fragShaderException[512];
        glGetShaderInfoLog(__shader_identity, 512, NULL, fragShaderException);
        Core::Console::Error<Console::HIG>("Failed to compile fragment shader due to :"_D, fragShaderException);
    }
    else {
        Core::Console::Debug<Console::MED>("Success in compiling fragment shader"_D);
    }
}

void Core::Shaders::FragmentShader::destroy() {
    glDeleteShader(__shader_identity);
    __shader_compiled = 0;
}
