cmake_minimum_required(VERSION 3.30.2)

set(PROJ_NAME "Voxel-Engine"    )
set(PROJ_LANG LANGUAGES CXX     )
set(PROJ_VERS VERSION  0.00.0   ) 
set(PROJ_DESC DESCRIPTION "implimentation of voxel engine.")

project(${PROJ_NAME} ${PROJ_DESC} ${PROJ_LANG} ${PROJ_VERS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" CACHE PATH "" FORCE)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" CACHE PATH "" FORCE)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" CACHE PATH "" FORCE)
add_subdirectory(submodules/Glfw)           # To generate Glfw libs.
#add_subdirectory(submodules/Glad/cmake)    # Not needed as it generates no bimaries.


set(ENGINE_ARC_OUT_DIR "${CMAKE_BINARY_DIR}/lib")
set(ENGINE_LIB_OUT_DIR "${CMAKE_BINARY_DIR}/bin")
set(ENGINE_RUN_OUT_DIR "${CMAKE_BINARY_DIR}/bin")

file(GLOB_RECURSE ENGINE_SOURCE
    "${CMAKE_SOURCE_DIR}/core/source/*.cpp"
    "${CMAKE_SOURCE_DIR}/core/include/*.h"
)

add_library(Engine SHARED ${ENGINE_SOURCE})
target_include_directories(Engine PUBLIC "${CMAKE_SOURCE_DIR}/core/include")
target_compile_definitions(Engine PRIVATE -DBUILD_CORE -DBUILD_PLATFORM_WIN)
set_target_properties(Engine PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
set_target_properties(Engine PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${ENGINE_ARC_OUT_DIR})
set_target_properties(Engine PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${ENGINE_LIB_OUT_DIR})
set_target_properties(Engine PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ENGINE_RUN_OUT_DIR})
target_compile_features(Engine PUBLIC cxx_std_20)


set(SANDBOX_ARC_OUT_DIR "${CMAKE_BINARY_DIR}/lib")
set(SANDBOX_LIB_OUT_DIR "${CMAKE_BINARY_DIR}/bin")
set(SANDBOX_RUN_OUT_DIR "${CMAKE_BINARY_DIR}/bin")

# temporary project to assist through development.
add_executable(Sandbox 
    "${CMAKE_SOURCE_DIR}/examples/Sandbox.cpp"
    "${CMAKE_SOURCE_DIR}/core/engine.h"
)
target_include_directories(Sandbox PUBLIC "${CMAKE_SOURCE_DIR}/core")
set_target_properties(Sandbox PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${SANDBOX_ARC_OUT_DIR})
set_target_properties(Sandbox PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${SANDBOX_LIB_OUT_DIR})
set_target_properties(Sandbox PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${SANDBOX_RUN_OUT_DIR})
target_link_libraries(Sandbox PUBLIC Engine)