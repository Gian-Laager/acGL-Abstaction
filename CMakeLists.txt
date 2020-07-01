cmake_minimum_required(VERSION 3.16)
project(acGL_Abstraction)

if (NOT DEFINED acGL_Abstraction_ROOT_DIR)
    set(acGL_Abstraction_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
endif()

set(CMAKE_CXX_STANDARD 17)

include_directories(${acGL_Abstraction_ROOT_DIR}/include)

set(SRC_FILES
        acGL_Abstraction src/acGL_Abstraction.cpp
)

set(PCH_H "${acGL_Abstraction_ROOT_DIR}/include/pch.h")

set(HEAD_FILES
        ${acGL_Abstraction_ROOT_DIR}/include/acGL_Abstraction.h
        ${acGL_Abstraction_ROOT_DIR}/include/pch.h)

find_package(glfw3 REQUIRED)
include_directories("deps/glew/include" "deps/glfw/include")
link_directories("deps/glew/lib" "deps/glfw/src/")

find_package(GLEW REQUIRED CONFIG)
find_package(OpenGL REQUIRED)

set(LIBS
        GLEW::GLEW
        glfw
)

add_library(${SRC_FILES} ${HEAD_FILES})
target_precompile_headers(${PROJECT_NAME} PRIVATE ${PCH_H})

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX _d)

target_link_libraries(${PROJECT_NAME} ${LIBS})
target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})

set(cgex $<CONFIGURATION>)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        -DGLEW_CMAKE_TEST_CONFIG=${cgex}
        -DGLEW_CMAKE_TEST_TARGET_FILE_NAME=$<TARGET_FILE_NAME:GLEW::GLEW>
        -DGLEW_CMAKE_TEST_TARGET_TYPE=$<TARGET_PROPERTY:GLEW::GLEW,TYPE>
        )

install(TARGETS ${PROJECT_NAME} DESTINATION bin)