cmake_minimum_required(VERSION 3.30.2)

set(PROJ_NAME "Voxel-Engine"    )
set(PROJ_LANG LANGUAGES CXX C   )
set(PROJ_VERS VERSION  0.00.0   ) 
set(PROJ_DESC DESCRIPTION "implimentation of voxel engine.")

project(${PROJ_NAME} ${PROJ_DESC} ${PROJ_LANG} ${PROJ_VERS})
find_package(OpenGL REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" CACHE PATH "" FORCE)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" CACHE PATH "" FORCE)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" CACHE PATH "" FORCE)
set(CMAKE_GLFW_INCLUDE_DIRECTORY "${CMAKE_SOURCE_DIR}/submodules/Glfw/include")
add_subdirectory(submodules/Glfw)           # To generate Glfw libs.
set(CMAKE_GLAD_INCLUDE_DIRECTORY "${CMAKE_SOURCE_DIR}/submodules/Glad/include")
set(CMAKE_GLAD_SOURCES_DIRECTORY "${CMAKE_SOURCE_DIR}/submodules/Glad/src")
#add_subdirectory(submodules/Glad/cmake)    # Not needed as it generates no bimaries.


set(ENGINE_ARC_OUT_DIR "${CMAKE_BINARY_DIR}/lib")
set(ENGINE_LIB_OUT_DIR "${CMAKE_BINARY_DIR}/bin")
set(ENGINE_RUN_OUT_DIR "${CMAKE_BINARY_DIR}/bin")

file(GLOB ENGINE_RESOURCE_FILES 
    "${CMAKE_SOURCE_DIR}/core/resources/images/*"
    "${CMAKE_SOURCE_DIR}/core/resources/shaders/*"
)
source_group("Resources" FILES ${ENGINE_RESOURCE_FILES})

file(GLOB_RECURSE ENGINE_SOURCE
    "${CMAKE_SOURCE_DIR}/core/source/*.cpp"
    "${CMAKE_SOURCE_DIR}/core/include/*.h"
    "${CMAKE_GLAD_SOURCES_DIRECTORY}/glad.c"
)

add_library(Engine SHARED ${ENGINE_SOURCE})
target_sources(Engine PRIVATE ${ENGINE_RESOURCE_FILES})
target_include_directories(Engine PUBLIC "${CMAKE_SOURCE_DIR}/core/include")
target_compile_definitions(Engine PRIVATE -DBUILD_CORE -DBUILD_PLATFORM_WIN)
target_precompile_headers(Engine PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${CMAKE_SOURCE_DIR}/core/include/pch.h>)
target_compile_features(Engine PUBLIC cxx_std_20)
set_target_properties(Engine PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
set_target_properties(Engine PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${ENGINE_ARC_OUT_DIR})
set_target_properties(Engine PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${ENGINE_LIB_OUT_DIR})
set_target_properties(Engine PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ENGINE_RUN_OUT_DIR})
target_include_directories(Engine PUBLIC ${CMAKE_GLAD_INCLUDE_DIRECTORY})
target_include_directories(Engine PUBLIC ${CMAKE_GLFW_INCLUDE_DIRECTORY})
target_link_libraries(Engine PUBLIC glfw)
target_link_libraries(Engine PUBLIC OpenGL::GL)


set(SANDBOX_ARC_OUT_DIR "${CMAKE_BINARY_DIR}/lib")
set(SANDBOX_LIB_OUT_DIR "${CMAKE_BINARY_DIR}/bin")
set(SANDBOX_RUN_OUT_DIR "${CMAKE_BINARY_DIR}/bin")

# temporary project to assist through development.
add_executable(Sandbox 
    "${CMAKE_SOURCE_DIR}/examples/Sandbox.cpp"
    "${CMAKE_SOURCE_DIR}/core/engine.h"
    "${CMAKE_GLAD_SOURCES_DIRECTORY}/glad.c"
)
target_include_directories(Sandbox PUBLIC "${CMAKE_SOURCE_DIR}/core")
set_target_properties(Sandbox PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${SANDBOX_ARC_OUT_DIR})
set_target_properties(Sandbox PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${SANDBOX_LIB_OUT_DIR})
set_target_properties(Sandbox PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${SANDBOX_RUN_OUT_DIR})
target_link_libraries(Sandbox PRIVATE Engine)