#pragma once

#include "api.hpp"
#include "application.hpp"
#include "exceptions.hpp"

namespace Engine {

	ENGINE_API void RegisterApplication(Application* (*function)(void));

	namespace Startup {

