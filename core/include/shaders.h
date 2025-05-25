#ifndef CORE_SHADERS_H
#define CORE_SHADERS_H

#include "platform.h"
#include "logging.h"
#include "pch.h"

#include "glad/glad.h"
#include "glfw/glfw3.h"

namespace Core::Shaders {

	using Source = const char*;

	namespace Base {

		class IShaderBase {
		protected:
			Source __shader_source;
			uInt32 __shader_identity;
			sInt32 __shader_compiled;
		public:
			IShaderBase(String src, GLenum shaderType);
			virtual ~IShaderBase();
		public:
			virtual void compile() = 0;
			virtual void destroy() = 0;
		public:
			uInt32 getIdentity();
			sInt32 getCompiled();
		};

	};

	class VertexShader : public Base::IShaderBase {
	public:
		VertexShader(String source) : Base::IShaderBase(source, GL_VERTEX_SHADER) {}
	public:
		void compile() override;
		void destroy() override;
	};

};

#endif