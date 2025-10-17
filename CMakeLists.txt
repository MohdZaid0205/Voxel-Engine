cmake_minimum_required(VERSION 3.30.2)

set(PROJ_NAME "Voxel-Engine"    )
set(PROJ_LANG LANGUAGES CXX C   )
set(PROJ_VERS VERSION  0.00.0   ) 
set(PROJ_DESC DESCRIPTION "implimentation of voxel engine.")

project(${PROJ_NAME} ${PROJ_DESC} ${PROJ_LANG} ${PROJ_VERS})

find_package    (OpenGL REQUIRED)
include         (GoogleTest     )
enable_testing  (               )

set(CMAKE_CXX_STANDARD 20           )
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/bin" CACHE PATH "" FORCE)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/bin" CACHE PATH "" FORCE)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/lib" CACHE PATH "" FORCE)
set(CMAKE_GTEST_INCLUDE_DIRECTORY   "${CMAKE_SOURCE_DIR}/submodules/GTest/include/getst")
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


# [ COMMON ]:
set(COMMON_ARC_OUT_DIR "${CMAKE_BINARY_DIR}/lib")
set(COMMON_LIB_OUT_DIR "${CMAKE_BINARY_DIR}/bin")
set(COMMON_RUN_OUT_DIR "${CMAKE_BINARY_DIR}/bin")
set(COMMON_BSE_INP_DIR "${CMAKE_SOURCE_DIR}/common"         )
set(COMMON_INL_INP_DIR "${CMAKE_SOURCE_DIR}/common/inline"  )
set(COMMON_SRC_INP_DIR "${CMAKE_SOURCE_DIR}/common/source"  )
set(COMMON_INC_INP_DIR "${CMAKE_SOURCE_DIR}/common/include" )

file(GLOB_RECURSE COMMON_INLINE_FILES "${COMMON_INL_INP_DIR}/*.tpp" "${COMMON_INL_INP_DIR}/*.inl")
file(GLOB_RECURSE COMMON_SOURCE_FILES "${COMMON_SRC_INP_DIR}/*.cpp" "${COMMON_INC_INP_DIR}/*.h"  )
source_group("Inline Files" FILES ${COMMON_INLINE_FILES})

add_library                 (Common STATIC  "${COMMON_SOURCE_FILES}")
target_sources              (Common PRIVATE "${COMMON_INLINE_FILES}")
target_include_directories  (Common PUBLIC  "${COMMON_BSE_INP_DIR}" )
target_include_directories  (Common PUBLIC  "${COMMON_INC_INP_DIR}" )
target_include_directories  (Common PUBLIC  "${COMMON_INL_INP_DIR}" )
set_target_properties       (Common PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${COMMON_ARC_OUT_DIR}")
set_target_properties       (Common PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${COMMON_LIB_OUT_DIR}")
set_target_properties       (Common PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${COMMON_RUN_OUT_DIR}")
target_compile_definitions  (Common PRIVATE -DBUILD_COMMON -DBUILD_PLATFORM_WIN)

target_precompile_headers   (Common PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${COMMON_INC_INP_DIR}/pch.h>)


# [ STRUCTURES ]:
set(STRUCTURES_ARC_OUT_DIR "${CMAKE_BINARY_DIR}/lib")
set(STRUCTURES_LIB_OUT_DIR "${CMAKE_BINARY_DIR}/bin")
set(STRUCTURES_RUN_OUT_DIR "${CMAKE_BINARY_DIR}/bin")
set(STRUCTURES_BSE_INP_DIR "${CMAKE_SOURCE_DIR}/structures"         )
set(STRUCTURES_INL_INP_DIR "${CMAKE_SOURCE_DIR}/structures/inline"  )
set(STRUCTURES_SRC_INP_DIR "${CMAKE_SOURCE_DIR}/structures/source"  )
set(STRUCTURES_INC_INP_DIR "${CMAKE_SOURCE_DIR}/structures/include" )

file(GLOB_RECURSE STRUCTURES_INLINE_FILES "${STRUCTURES_INL_INP_DIR}/*.tpp" "${STRUCTURES_INL_INP_DIR}/*.inl")
file(GLOB_RECURSE STRUCTURES_SOURCE_FILES "${STRUCTURES_SRC_INP_DIR}/*.cpp" "${STRUCTURES_INC_INP_DIR}/*.h"  )
source_group("Inline Files" FILES ${STRUCTURES_INLINE_FILES})

add_library                 (Structures STATIC  "${STRUCTURES_SOURCE_FILES}")
target_sources              (Structures PRIVATE "${STRUCTURES_INLINE_FILES}")
target_include_directories  (Structures PUBLIC  "${STRUCTURES_BSE_INP_DIR}" )
target_include_directories  (Structures PUBLIC  "${STRUCTURES_INC_INP_DIR}" )
target_include_directories  (Structures PUBLIC  "${STRUCTURES_INL_INP_DIR}" )
set_target_properties       (Structures PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${STRUCTURES_ARC_OUT_DIR}")
set_target_properties       (Structures PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${STRUCTURES_LIB_OUT_DIR}")
set_target_properties       (Structures PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${STRUCTURES_RUN_OUT_DIR}")


# [ ENGINE ]:
set(ENGINE_ARC_OUT_DIR "${CMAKE_BINARY_DIR}/lib")
set(ENGINE_LIB_OUT_DIR "${CMAKE_BINARY_DIR}/bin")
set(ENGINE_RUN_OUT_DIR "${CMAKE_BINARY_DIR}/bin")
set(ENGINE_BSE_INP_DIR "${CMAKE_SOURCE_DIR}/engine"          )
set(ENGINE_DOX_INP_DIR "${CMAKE_SOURCE_DIR}/engine/docs"     )
set(ENGINE_INC_INP_DIR "${CMAKE_SOURCE_DIR}/engine/include"  )
set(ENGINE_INL_INP_DIR "${CMAKE_SOURCE_DIR}/engine/inline"   )
set(ENGINE_RES_INP_DIR "${CMAKE_SOURCE_DIR}/engine/resources")
set(ENGINE_SRC_INP_DIR "${CMAKE_SOURCE_DIR}/engine/source"   )

file(GLOB_RECURSE ENGINE_DOCSRC_FILES "${ENGINE_DOX_INP_DIR}/*.md"   "${ENGINE_DOX_INP_DIR}/*.txt" )
file(GLOB_RECURSE ENGINE_SOURCE_FILES "${ENGINE_SRC_INP_DIR}/*.cpp"  "${ENGINE_INC_INP_DIR}/*.h"   )
file(GLOB_RECURSE ENGINE_INLINE_FILES "${ENGINE_INL_INP_DIR}/*.tpp"  "${ENGINE_INL_INP_DIR}/*.inl" )
file(GLOB_RECURSE ENGINE_RESSRC_FILES "${ENGINE_RES_INP_DIR}/*.vert" "${ENGINE_RES_INP_DIR}/*.frag")
source_group("Inline Files"         FILES ${ENGINE_INLINE_FILES})
source_group("Resources Files"      FILES ${ENGINE_RESSRC_FILES})
source_group("Documentation Files"  FILES ${ENGINE_DOCSRC_FILES})

add_library                 (Engine SHARED  "${ENGINE_SOURCE_FILES}")
target_sources              (Engine PRIVATE "${GLAD_SOURCE_FILES}"  )
target_sources              (Engine PRIVATE "${ENGINE_INLINE_FILES}") 
target_sources              (Engine PRIVATE "${ENGINE_DOCSRC_FILES}")
target_sources              (Engine PRIVATE "${ENGINE_RESSRC_FILES}") 
target_include_directories  (Engine PUBLIC  "${ENGINE_BSE_INP_DIR}" )
target_include_directories  (Engine PUBLIC  "${ENGINE_INC_INP_DIR}" )
target_include_directories  (Engine PUBLIC  "${ENGINE_INL_INP_DIR}" )

target_link_libraries       (Engine PUBLIC  Common      ) # implicitly inherit common include directory
target_link_libraries       (Engine PUBLIC  glfw        ) # explicitly inherit glfw   include directory
target_link_libraries       (Engine PUBLIC  OpenGL::GL  ) # explicitly inherit opengl include directory
target_link_libraries       (Engine PUBLIC  Structures  ) # implicitly inherit struct include directory
target_include_directories  (Engine PUBLIC "${CMAKE_GLAD__INCLUDE_DIRECTORY}")
target_include_directories  (Engine PUBLIC "${CMAKE_GLFW__INCLUDE_DIRECTORY}")
set_target_properties       (Engine PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
set_target_properties       (Engine PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${ENGINE_ARC_OUT_DIR})
set_target_properties       (Engine PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${ENGINE_LIB_OUT_DIR})
set_target_properties       (Engine PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ENGINE_RUN_OUT_DIR})


# TODO: add support for Gtest for structures module, setup and run

# [ SANDBOX ]: temporary project to assist through development.
set(SANDBOX_ARC_OUT_DIR "${CMAKE_BINARY_DIR}/lib")
set(SANDBOX_LIB_OUT_DIR "${CMAKE_BINARY_DIR}/bin")
set(SANDBOX_RUN_OUT_DIR "${CMAKE_BINARY_DIR}/bin")
set(SANDBOX_BSE_INP_DIR "${CMAKE_SOURCE_DIR}/examples"         )
set(SANDBOX_INL_INP_DIR "${CMAKE_SOURCE_DIR}/examples/inline"  )
set(SANDBOX_SRC_INP_DIR "${CMAKE_SOURCE_DIR}/examples/source"  )
set(SANDBOX_INC_INP_DIR "${CMAKE_SOURCE_DIR}/examples/include" )

file(GLOB_RECURSE SANDBOX_INLINE_FILES "${SANDBOX_INL_INP_DIR}/*.tpp" "${SANDBOX_INL_INP_DIR}/*.inl")
file(GLOB_RECURSE SANDBOX_SOURCE_FILES "${SANDBOX_SRC_INP_DIR}/*.cpp" "${SANDBOX_INC_INP_DIR}/*.h"  )
source_group("Inline Files" FILES ${SANDBOX_INLINE_FILES})

add_executable              (Sandbox "${SANDBOX_SOURCE_FILES}")
target_sources              (Sandbox PRIVATE "${GLAD_SOURCE_FILES}"               )
target_include_directories  (Sandbox PUBLIC  "${ENGINE_BSE_INP_DIR}"              )
target_include_directories  (Sandbox PUBLIC  "${COMMON_ARC_OUT_DIR}"              )
target_include_directories  (Sandbox PUBLIC  "${STRUCTURES_BSE_INP_DIR}"          )
target_include_directories  (Sandbox PUBLIC  "${CMAKE_GLAD__INCLUDE_DIRECTORY}"   )
set_target_properties(Sandbox PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${SANDBOX_ARC_OUT_DIR})
set_target_properties(Sandbox PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${SANDBOX_LIB_OUT_DIR})
set_target_properties(Sandbox PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${SANDBOX_RUN_OUT_DIR})
target_link_libraries(Sandbox PUBLIC  Engine    )
target_link_libraries(Sandbox PRIVATE Common    )
target_link_libraries(Sandbox PRIVATE Structures)