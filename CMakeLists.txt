cmake_minimum_required(VERSION 3.30)

# define basic information about this project ------------------------------------------+
set(PROJ_NAME "VOXEL-ENGINE"                )                       #                   |
set(PROJ_VERS VERSION 0.00.1                )                       #                   |
set(PROJ_LANG LANGUAGES CXX CSharp C        )                       #                   |
set(PROJ_DESC DESCRIPTION "")                                       # empty for now     |
# --------------------------------------------------------------------------------------+

project(${PROJ_NAME} ${PROJ_DESC} ${PROJ_LANG} ${PROJ_VERS})
find_package(OpenGL REQUIRED)

# to set outpiut directory of binaries both engine and editor
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/bin" CACHE PATH "" FORCE)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/bin" CACHE PATH "" FORCE)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/lib" CACHE PATH "" FORCE)
set(CMAKE_GTEST_INCLUDE_DIRECTORY   "${CMAKE_SOURCE_DIR}/submodules/GTest/include/gtest")
set(CMAKE_GTEST_SOURCES_DIRECTORY   "${CMAKE_SOURCE_DIR}/submodules/GTest/src"          )
set(CMAKE_GLFW__INCLUDE_DIRECTORY   "${CMAKE_SOURCE_DIR}/submodules/Glfw/include"       )
set(CMAKE_GLAD__INCLUDE_DIRECTORY   "${CMAKE_SOURCE_DIR}/submodules/Glad/include"       )
set(CMAKE_GLAD__SOURCES_DIRECTORY   "${CMAKE_SOURCE_DIR}/submodules/Glad/src"           )

# add submodules for build -------------------------------------------------------------+
add_subdirectory(submodules/Glfw )          # To generate Glfw libs.                    |
add_subdirectory(submodules/GTest)          # To use GTest for testing.                 |
#add_subdirectory(submodules/Glad/cmake)    # Not needed as it generates no binaries.   |
# --------------------------------------------------------------------------------------+

# to put all gtest stuff into a folder named GTEST -------------------------------------+
foreach(target IN ITEMS gtest gtest_main gmock gmock_main)          #                   |
    if(TARGET ${target})                                            #                   |
        set_target_properties(${target} PROPERTIES FOLDER "GTEST")  #                   |
    endif()                                                         #                   |
endforeach()                                                        #                   |
# --------------------------------------------------------------------------------------+

# prepare glad source and include files ------------------------------------------------+
file(GLOB_RECURSE GLAD_SOURCE_FILES                                 #                   |
    "${CMAKE_GLAD__SOURCES_DIRECTORY}/glad.c"                       #                   |
    "${CMAKE_GLAD__INCLUDE_DIRECTORY}/glad.h"                       #                   |
)                                                                   #                   |
source_group("Vendor Files" FILES ${GLAD_SOURCE_FILES})             #                   |
# --------------------------------------------------------------------------------------+

# [ ENGINE ]:
set(ENGINE_BSE_INP_DIR "${CMAKE_SOURCE_DIR}/engine"             )
set(ENGINE_INC_INP_DIR "${CMAKE_SOURCE_DIR}/engine/include"     )
set(ENGINE_SRC_INP_DIR "${CMAKE_SOURCE_DIR}/engine/source"      )
set(ENGINE_DOX_INP_DIR "${CMAKE_SOURCE_DIR}/engine"             )   # TODO: create documentaion
set(ENGINE_RES_INP_DIR "${CMAKE_SOURCE_DIR}/engine"             )   # TODO: create resource dir

file(GLOB_RECURSE ENGINE_DOCSRC_FILES "${ENGINE_DOX_INP_DIR}/*.md"   "${ENGINE_DOX_INP_DIR}/*.txt" )
file(GLOB_RECURSE ENGINE_SOURCE_FILES "${ENGINE_SRC_INP_DIR}/*.cpp"  "${ENGINE_INC_INP_DIR}/*.h"   )
file(GLOB_RECURSE ENGINE_RESSRC_FILES "${ENGINE_RES_INP_DIR}/*.vert" "${ENGINE_RES_INP_DIR}/*.frag")
source_group("Resources Files"      FILES ${ENGINE_RESSRC_FILES})
source_group("Documentation Files"  FILES ${ENGINE_DOCSRC_FILES})

add_library                 (Engine SHARED  "${ENGINE_SOURCE_FILES}")
target_sources              (Engine PRIVATE "${GLAD_SOURCE_FILES}"  )
target_sources              (Engine PRIVATE "${ENGINE_DOCSRC_FILES}")
target_sources              (Engine PRIVATE "${ENGINE_RESSRC_FILES}") 
target_include_directories  (Engine PUBLIC  "${ENGINE_BSE_INP_DIR}" )
target_include_directories  (Engine PUBLIC  "${ENGINE_INC_INP_DIR}" )

target_link_libraries       (Engine PUBLIC  glfw        ) # explicitly inherit glfw   include directory
target_link_libraries       (Engine PUBLIC  OpenGL::GL  ) # explicitly inherit opengl include directory
target_include_directories  (Engine PUBLIC "${CMAKE_GLAD__INCLUDE_DIRECTORY}")
target_include_directories  (Engine PUBLIC "${CMAKE_GLFW__INCLUDE_DIRECTORY}")
set_target_properties       (Engine PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON )
# following lines may be considerd redundant
# set_target_properties       (Engine PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${ENGINE_ARC_OUT_DIR})
# set_target_properties       (Engine PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${ENGINE_LIB_OUT_DIR})
# set_target_properties       (Engine PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ENGINE_RUN_OUT_DIR})
target_compile_definitions  (Engine PRIVATE -DBUILD_ENGINE -DBUILD_PLATFORM_WIN)
set_target_properties(Engine PROPERTIES VS_GLOBAL_ResolveNuGetPackages "false" )


set(EDITOR_BSE_INP_DIR "${CMAKE_SOURCE_DIR}/editor"             )
set(EDITOR_XML_INP_DIR "${CMAKE_SOURCE_DIR}/editor"             )
set(EDITOR_SRC_INP_DIR "${CMAKE_SOURCE_DIR}/editor"             )
set(EDITOR_DOX_INP_DIR "${CMAKE_SOURCE_DIR}/editor"             )   # TODO: create documentaion
set(EDITOR_RES_INP_DIR "${CMAKE_SOURCE_DIR}/editor"             )   # TODO: create resource dir

# [ EDITOR ]:
file(GLOB_RECURSE EDITOR_SOURCE_FILES "${EDITOR_SRC_INP_DIR}/*.cs"   "${EDITOR_SRC_INP_DIR}/*.cs*"   )
file(GLOB_RECURSE EDITOR_WPF_UI_FILES "${EDITOR_XML_INP_DIR}/*.xaml" "${EDITOR_XML_INP_DIR}/*.xaml.*")

add_executable       (Editor "${EDITOR_SOURCE_FILES}")
target_sources       (Editor PRIVATE "${EDITOR_WPF_UI_FILES}")

set_target_properties(Editor PROPERTIES VS_GLOBAL_UseWPF "true"                 )
set_target_properties(Editor PROPERTIES DOTNET_SDK "Microsoft.NET.Sdk"          )
set_target_properties(Editor PROPERTIES DOTNET_TARGET_FRAMEWORK "net8.0-windows")

add_dependencies    (Editor Engine)