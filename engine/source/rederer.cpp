#include "renderer.hpp"

Engine::String Engine::read_shader(String path){
    Engine::String shader_code;
    Engine::String due;

    Engine::Attempt::to<MED>([path, &shader_code, &due]() {

        try {
            std::ifstream shader_file;
            shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

            shader_file.open(path);
            std::stringstream shader_stream;
            shader_stream << shader_file.rdbuf();
            shader_file.close();
            shader_code = shader_stream.str();

            return Engine::Attempt::Status::PASS;

        } catch (std::ifstream::failure e){
            due = "File cannot be read";
            
            return Engine::Attempt::Status::FAIL;
        }

    }).does("Read shader file path="_D, path, "."_D)
        .pass("shader path"_D, path, "laoded sucessfully."_D)
        .fail("failed to read shader path="_D, path, due);
    return shader_code;
}

std::map<Engine::String, Engine::u32> Engine::VertexShader::compiled
    = std::map<Engine::String, Engine::u32>();

Engine::u32 Engine::VertexShader::compile(String vertex_path){
    Engine::u32 identifier = 0;
    Engine::i32 status = 0;
    char info_log[512];

    Engine::Attempt::to<HIG>([vertex_path ,&identifier, &status, &info_log]() {
        Engine::String vertex_string = Engine::read_shader(vertex_path);
        const char* vertex_code = vertex_string.c_str();
        identifier = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(identifier, 1, &vertex_code, NULL);
        glCompileShader(identifier);

        glGetShaderiv(identifier, GL_COMPILE_STATUS, &status);
        if (!status){
            glGetShaderInfoLog(identifier, 512, NULL, info_log);
            return Engine::Attempt::Status::FAIL;
        };

        return Engine::Attempt::Status::PASS;
    }).does("Compiling VERTEX SHADER path="_B, vertex_path)
        .pass("vertex shader path="_D, vertex_path, "Has been compile id="_B, identifier)
        .fail("failed to compile vertex shader path="_D, vertex_path, "due to:"_B, info_log);

    compiled[vertex_path] = identifier;
    return identifier;
}

Engine::u32 Engine::VertexShader::compile_or_get(String vertex_path){
    if (compiled.find(vertex_path) != compiled.end() && compiled[vertex_path] != 0)
        return compiled[vertex_path];
    return Engine::VertexShader::compile(vertex_path);
}

Engine::u32 Engine::VertexShader::get(String vertex_path){
    if (compiled.find(vertex_path) != compiled.end() && compiled[vertex_path] != 0)
        return compiled[vertex_path];
    return 0;
}

std::map<Engine::String, Engine::u32> Engine::FragmentShader::compiled
    = std::map<Engine::String, Engine::u32>();

Engine::u32 Engine::FragmentShader::compile(String fragment_path) {
    Engine::u32 identifier = 0;
    Engine::i32 status = 0;
    char info_log[512];

    Engine::Attempt::to<HIG>([fragment_path, &identifier, &status, &info_log]() {
        Engine::String fragment_string = Engine::read_shader(fragment_path);
        const char* fragment_code = fragment_string.c_str();
        identifier = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(identifier, 1, &fragment_code, NULL);
        glCompileShader(identifier);

        glGetShaderiv(identifier, GL_COMPILE_STATUS, &status);
        if (!status) {
            glGetShaderInfoLog(identifier, 512, NULL, info_log);
            return Engine::Attempt::Status::FAIL;
        };

        return Engine::Attempt::Status::PASS;
        }).does("Compiling FRAGMENT SHADER path="_B, fragment_path)
            .pass("fragment shader path="_D, fragment_path, "Has been compile id="_B, identifier)
            .fail("failed to compile fragment shader path="_D, fragment_path, "due to:"_B, info_log);

        compiled[fragment_path] = identifier;
        return identifier;
}

Engine::u32 Engine::FragmentShader::compile_or_get(String fragment_path) {
    if (compiled.find(fragment_path) != compiled.end() && compiled[fragment_path] != 0)
        return compiled[fragment_path];
    return Engine::FragmentShader::compile(fragment_path);
}

Engine::u32 Engine::FragmentShader::get(String fragment_path) {
    if (compiled.find(fragment_path) != compiled.end() && compiled[fragment_path] != 0)
        return compiled[fragment_path];
    return 0;
}

std::map<Engine::u32, std::pair<Engine::u32, Engine::u32>> Engine::ShaderProgram::programs
    = std::map<Engine::u32, std::pair<Engine::u32, Engine::u32>>();

