cmake_minimum_required(VERSION 3.30.2)

set(PROJ_NAME "Voxel-Engine"    )
set(PROJ_LANG LANGUAGES CXX C   )
set(PROJ_VERS VERSION  0.00.0   ) 
set(PROJ_DESC DESCRIPTION "implimentation of voxel engine.")

project(${PROJ_NAME} ${PROJ_DESC} ${PROJ_LANG} ${PROJ_VERS})

find_package(OpenGL REQUIRED)
include(GoogleTest)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" CACHE PATH "" FORCE)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" CACHE PATH "" FORCE)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" CACHE PATH "" FORCE)
set(CMAKE_GLFW_INCLUDE_DIRECTORY "${CMAKE_SOURCE_DIR}/submodules/Glfw/include")
add_subdirectory(submodules/Glfw)           # To generate Glfw libs.
set(CMAKE_GLAD_INCLUDE_DIRECTORY "${CMAKE_SOURCE_DIR}/submodules/Glad/include")
set(CMAKE_GLAD_SOURCES_DIRECTORY "${CMAKE_SOURCE_DIR}/submodules/Glad/src")
#add_subdirectory(submodules/Glad/cmake)    # Not needed as it generates no bimaries.
set(CMAKE_GTEST_INCLUDE_DIRECTORY "${CMAKE_SOURCE_DIR}/submodules/GTest/include/getst")
set(CMAKE_GTEST_SOURCES_DIRECTORY "${CMAKE_SOURCE_DIR}/submodules/GTest/src")
add_subdirectory(submodules/GTest)          # To use GTest for testing.

# to put all gtes t stuff into a folder named GTEST
foreach(target IN ITEMS gtest gtest_main gmock gmock_main)
    if(TARGET ${target})
        set_target_properties(${target} PROPERTIES FOLDER "GTEST")
    endif()
endforeach()

# STRUCTURES:
set(STRUCT_ARC_OUT_DIR "${CMAKE_BINARY_DIR}/lib")
set(STRUCT_LIB_OUT_DIR "${CMAKE_BINARY_DIR}/bin")
set(STRUCT_RUN_OUT_DIR "${CMAKE_BINARY_DIR}/bin")

file(GLOB STRUCT_INLINE_FILES 
    "${CMAKE_SOURCE_DIR}/structures/include/*.tpp"
    "${CMAKE_SOURCE_DIR}/structures/include/*.inl"
)
source_group("Template Files" FILES ${STRUCT_INLINE_FILES})

file(GLOB_RECURSE STRUCT_SOURCE
    "${CMAKE_SOURCE_DIR}/structures/source/*.cpp"
    "${CMAKE_SOURCE_DIR}/structures/include/*.h"
)

add_library(Structures STATIC "${STRUCT_SOURCE}")
target_sources(Structures PRIVATE ${STRUCT_INLINE_FILES})
target_include_directories(Structures PUBLIC "${CMAKE_SOURCE_DIR}/structures/include")
set_target_properties(Structures PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${STRUCT_ARC_OUT_DIR})
set_target_properties(Structures PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${STRUCT_LIB_OUT_DIR})
set_target_properties(Structures PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${STRUCT_RUN_OUT_DIR})

file(GLOB_RECURSE STRUCT_TESTS
    "${CMAKE_SOURCE_DIR}/structures/tests/*.cpp"
    "${CMAKE_SOURCE_DIR}/structures/tests/*.h"
    "${CMAKE_SOURCE_DIR}/structures/structures.h"
)

add_executable(structuresTest "${STRUCT_TESTS}")
target_include_directories(Structures PUBLIC "${CMAKE_SOURCE_DIR}/structures")
target_link_libraries(structuresTest PRIVATE Structures)
target_link_libraries(structuresTest PRIVATE gtest_main)
gtest_discover_tests(structuresTest)
set_target_properties(structuresTest PROPERTIES FOLDER "Tests")

# ENGINE:
set(ENGINE_ARC_OUT_DIR "${CMAKE_BINARY_DIR}/lib")
set(ENGINE_LIB_OUT_DIR "${CMAKE_BINARY_DIR}/bin")
set(ENGINE_RUN_OUT_DIR "${CMAKE_BINARY_DIR}/bin")

file(GLOB ENGINE_RESOURCE_FILES 
    "${CMAKE_SOURCE_DIR}/core/resources/images/*"
    "${CMAKE_SOURCE_DIR}/core/resources/shaders/*"
)
source_group("Resources Files" FILES ${ENGINE_RESOURCE_FILES})

file(GLOB ENGINE_DOCUMENTATION_FILES
    "${CMAKE_SOURCE_DIR}/core/docs/*.md"
    "${CMAKE_SOURCE_DIR}/core/docs/mkdocs.yml"
    "${CMAKE_SOURCE_DIR}/core/docs/dev-side/*.md"
)
source_group("Documentaion Files" FILES ${ENGINE_DOCUMENTATION_FILES})

file(GLOB_RECURSE ENGINE_SOURCE
    "${CMAKE_SOURCE_DIR}/core/source/*.cpp"
    "${CMAKE_SOURCE_DIR}/core/include/*.h"
    "${CMAKE_GLAD_SOURCES_DIRECTORY}/glad.c"
    "${CMAKE_SOURCE_DIR}/structures/structures.h"
)

add_library(Engine SHARED ${ENGINE_SOURCE})
target_sources(Engine PRIVATE ${ENGINE_DOCUMENTATION_FILES})
target_sources(Engine PRIVATE ${ENGINE_RESOURCE_FILES})
target_include_directories(Engine PUBLIC "${CMAKE_SOURCE_DIR}/core/include")
target_include_directories(Engine PUBLIC "${CMAKE_SOURCE_DIR}/structures")
target_compile_definitions(Engine PRIVATE -DBUILD_CORE -DBUILD_PLATFORM_WIN)
target_precompile_headers(Engine PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${CMAKE_SOURCE_DIR}/core/include/pch.h>)
target_compile_features(Engine PUBLIC cxx_std_20)
set_target_properties(Engine PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
set_target_properties(Engine PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${ENGINE_ARC_OUT_DIR})
set_target_properties(Engine PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${ENGINE_LIB_OUT_DIR})
set_target_properties(Engine PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ENGINE_RUN_OUT_DIR})
target_include_directories(Engine PUBLIC ${CMAKE_GLAD_INCLUDE_DIRECTORY})
target_include_directories(Engine PUBLIC ${CMAKE_GLFW_INCLUDE_DIRECTORY})
target_link_libraries(Engine PUBLIC Structures)
target_link_libraries(Engine PUBLIC glfw)
target_link_libraries(Engine PUBLIC OpenGL::GL)


# SANDBOX:
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