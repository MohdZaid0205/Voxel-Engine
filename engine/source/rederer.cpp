#include "renderer.hpp"

Engine::String Engine::read_shader(String path){
    Engine::String shader_code;
    Engine::String due;

    Engine::Attempt::to<LOW>([path, &shader_code, &due]() {

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

    Engine::Attempt::to<MED>([vertex_path ,&identifier, &status, &info_log]() {
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
        .pass("vertex shader path="_D, vertex_path, "Has been compile id="_D, identifier)
        .fail("failed to compile vertex shader path="_D, vertex_path, "due to:"_D, info_log);

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

    Engine::Attempt::to<MED>([fragment_path, &identifier, &status, &info_log]() {
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
        .pass("fragment shader path="_D, fragment_path, "Has been compile id="_D, identifier)
        .fail("failed to compile fragment shader path="_D, fragment_path, "due to:"_D, info_log);

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

std::map<std::pair<Engine::u32, Engine::u32>, Engine::u32> Engine::ShaderProgram::programs
    = std::map<std::pair<Engine::u32, Engine::u32>, Engine::u32>();

std::map<Engine::String, Engine::u32> Engine::ShaderProgram::named_programs
    = std::map<Engine::String, Engine::u32>();

Engine::u32 Engine::ShaderProgram::create_program(String v_path, String f_path){
    Engine::u32 v_shader = Engine::VertexShader::compile_or_get(v_path);
    Engine::u32 f_shader = Engine::FragmentShader::compile_or_get(f_path);
    return Engine::ShaderProgram::create_program(v_shader, f_shader);
}

Engine::u32 Engine::ShaderProgram::create_program(u32 v_shader, u32 f_shader){
    Engine::u32 identifier = 0;
    Engine::i32 status = 0;
    char info_log[512];

    Engine::Attempt::to<MED>([&identifier, &status, &info_log, v_shader, f_shader]() {
        identifier = glCreateProgram();
        glAttachShader(identifier, v_shader);
        glAttachShader(identifier, f_shader);
        glLinkProgram(identifier);
        glGetProgramiv(identifier, GL_LINK_STATUS, &status);
        if (!status) {
            glGetProgramInfoLog(identifier, 512, NULL, info_log);
            return Engine::Attempt::Status::FAIL;
        }
        return Engine::Attempt::Status::PASS;
    }).does("Creating PROGRAM using v_shader="_B, v_shader, "& f_shader="_B, f_shader)
        .pass("Creation for PROGRAM finished using v_shader="_D, v_shader, "& f_shader="_D, f_shader)
        .fail("Failed to create program due to:"_D, info_log);
    programs[std::pair<Engine::u32, Engine::u32>(v_shader, f_shader)] = identifier;
    return identifier;
}

Engine::u32 Engine::ShaderProgram::create_fragment_default_vertex(u32 f_shader){
    return Engine::ShaderProgram::create_program(0, f_shader);
}

Engine::u32 Engine::ShaderProgram::create_vertex_default_fragment(u32 v_shader){
    return Engine::ShaderProgram::create_program(v_shader, 0);
}

void Engine::ShaderProgram::name_program(String name, u32 id){
    named_programs[name] = id;
}

Engine::u32 Engine::ShaderProgram::get(u32 v_shader, u32 f_shader){
    auto which = std::pair(v_shader, f_shader);
    if (programs.find(which) != programs.end() && programs[which] != 0)
        return programs[which];
    return 0;
}

Engine::u32 Engine::ShaderProgram::get(String name){
    if (named_programs.find(name) != named_programs.end() && named_programs[name] != 0)
        return named_programs[name];
    return 0;
}
