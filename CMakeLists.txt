cmake_minimum_required(VERSION 3.30.2)

set(PROJ_NAME "Voxel-Engine"    )
set(PROJ_LANG LANGUAGES CXX     )
set(PROJ_VERS VERSION  0.00.0   ) 
set(PROJ_DESC DESCRIPTION "implimentation of voxel engine.")

project(${PROJ_NAME} ${PROJ_DESC} ${PROJ_LANG} ${PROJ_VERS})

file(GLOB_RECURSE ENGINE_SOURCE
    "${CMAKE_SOURCE_DIR}/core/source/*.cpp"
    "${CMAKE_SOURCE_DIR}/core/include/*.h"
)

add_library(Engine SHARED ${ENGINE_SOURCE})
target_include_directories(Engine PUBLIC "${CMAKE_SOURCE_DIR}/core/include")
target_compile_definitions(Engine PRIVATE -DBUILD_CORE -DBUILD_PLATFORM_WIN)
set_target_properties(Engine PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
target_compile_features(Engine PUBLIC cxx_std_20)

# temporary project to assist through development.
add_executable(Sandbox 
    "${CMAKE_SOURCE_DIR}/examples/Sandbox.cpp"
    "${CMAKE_SOURCE_DIR}/core/engine.h"
)
target_include_directories(Sandbox PUBLIC "${CMAKE_SOURCE_DIR}/core")
target_link_libraries(Sandbox PUBLIC Engine)