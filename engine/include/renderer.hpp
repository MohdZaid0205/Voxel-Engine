#pragma once

#include "api.hpp"
#include "events.hpp"

namespace Engine {

	String read_shader(String path);

	class VertexShader {
	private:
		static std::map<String, u32> compiled;
	public:
		static u32 compile(String vertex_path);
		static u32 compile_or_get(String vertex_path);
		static u32 get(String vertex_path);
	};

	class FragmentShader {
	private:
		static std::map<String, u32> compiled;
	public:
		static u32 compile(String fragment_path);
		static u32 compile_or_get(String fragment_path);
		static u32 get(String fragment_path);
	};

	class ShaderProgram {
	private:
		static std::map<std::pair<u32, u32>, u32> programs;
		static std::map<String, u32> named_programs;
	public:
		static u32 create_program(String v_path, String f_path);
		static u32 create_program(u32 v_shader, u32 f_shader);
		static u32 create_fragment_default_vertex(u32 f_shader);
		static u32 create_vertex_default_fragment(u32 v_shader);
		static void name_program(String name, u32 id);
	public:
		static u32 get(u32 v_shader, u32 f_shader);
		static u32 get(String name);
	};

};