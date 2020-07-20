cmake_minimum_required(VERSION 3.16)
set(P_PROJECT_NAME ${PROJECT_NAME})
project(acGL_Abstraction)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(target ${PROJECT_NAME})


if (NOT DEFINED acGL_Abstraction_ROOT_DIR)
    set(acGL_Abstraction_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
endif ()

include_directories(${acGL_Abstraction_ROOT_DIR}/include)

set(SRC_FILES
        ${acGL_Abstraction_ROOT_DIR}/src/acGL_Abstraction.cpp
        ${acGL_Abstraction_ROOT_DIR}/src/VertexBuffer.cpp
        ${acGL_Abstraction_ROOT_DIR}/src/Renderer.cpp
        ${acGL_Abstraction_ROOT_DIR}/src/VertexArray.cpp
        ${acGL_Abstraction_ROOT_DIR}/src/IndexBuffer.cpp
        ${acGL_Abstraction_ROOT_DIR}/src/VertexBufferLayout.cpp
        ${acGL_Abstraction_ROOT_DIR}/src/Shader.cpp
        ${acGL_Abstraction_ROOT_DIR}/src/Buffer.cpp
        ${acGL_Abstraction_ROOT_DIR}/src/Texture.cpp
        ${acGL_Abstraction_ROOT_DIR}/src/Window.cpp
        ${acGL_Abstraction_ROOT_DIR}/src/VertexArrayRenderer.cpp
        ${acGL_Abstraction_ROOT_DIR}/src/VertexBufferRenderer.cpp
        ${acGL_Abstraction_ROOT_DIR}/src/VertexIndexBufferRenderer.cpp

        #Dependencies
        ${acGL_Abstraction_ROOT_DIR}/deps/stb/stb_image.cpp
        )

set(PCH_H "${acGL_Abstraction_ROOT_DIR}/include/pch.h")

set(HEAD_FILES
        ${acGL_Abstraction_ROOT_DIR}/include/acGL_Abstraction.h
        ${acGL_Abstraction_ROOT_DIR}/include/pch.h
        ${acGL_Abstraction_ROOT_DIR}/include/Renderer.h
        ${acGL_Abstraction_ROOT_DIR}/include/VertexBuffer.h
        ${acGL_Abstraction_ROOT_DIR}/include/VertexArray.h
        ${acGL_Abstraction_ROOT_DIR}/include/IndexBuffer.h
        ${acGL_Abstraction_ROOT_DIR}/include/Shader.h
        ${acGL_Abstraction_ROOT_DIR}/include/VertexBufferLayout.h
        ${acGL_Abstraction_ROOT_DIR}/include/Buffer.h
        ${acGL_Abstraction_ROOT_DIR}/include/Texture.h
        ${acGL_Abstraction_ROOT_DIR}/include/Window.h
        ${acGL_Abstraction_ROOT_DIR}/include/VertexArrayRenderer.h
        ${acGL_Abstraction_ROOT_DIR}/include/VertexBufferRenderer.h
        ${acGL_Abstraction_ROOT_DIR}/include/VertexIndexBufferRenderer.h

        #Dependencies
        ${acGL_Abstraction_ROOT_DIR}/deps/stb/stb_image.h

        ${acGL_Abstraction_ROOT_DIR}/deps/glm/glm/glm.hpp
        ${acGL_Abstraction_ROOT_DIR}/deps/glm/glm/gtx/string_cast.hpp
        ${acGL_Abstraction_ROOT_DIR}/deps/glm/glm/gtc/type_ptr.hpp
        )

find_package(glfw3 REQUIRED)

set(GLEW_DIR ${acGL_Abstraction_ROOT_DIR}/deps/glew)
find_package(GLEW REQUIRED)

include_directories(
        "${acGL_Abstraction_ROOT_DIR}/deps/glew/include"
        "${acGL_Abstraction_ROOT_DIR}/deps/glfw/include"
        "${acGL_Abstraction_ROOT_DIR}/deps/stb"
        "${acGL_Abstraction_ROOT_DIR}/deps/glm/glm"
)
link_directories(
        "${acGL_Abstraction_ROOT_DIR}/deps/glew/lib"
        "${acGL_Abstraction_ROOT_DIR}/deps/glfw/src/"
)

find_package(OpenGL REQUIRED)

set(LIBS
        "${acGL_Abstraction_ROOT_DIR}/deps/glew/lib/libGLEW.a"
        "${OPENGL_LIBRARIES}"
        "${acGL_Abstraction_ROOT_DIR}/deps/glfw/src/libglfw.3.dylib"
        )

add_library(${target} SHARED ${SRC_FILES} ${HEAD_FILES})
target_precompile_headers(${target} PRIVATE ${PCH_H})

set_target_properties(${target} PROPERTIES DEBUG_POSTFIX _d)

target_link_libraries(${target} ${LIBS})
target_include_directories(${target} PRIVATE ${OPENGL_INCLUDE_DIR})


set(cgex $<CONFIGURATION>)

target_compile_definitions(${target} PRIVATE
        -DGLEW_CMAKE_TEST_CONFIG=${cgex}
        -DGLEW_CMAKE_TEST_TARGET_FILE_NAME=$<TARGET_FILE_NAME:GLEW::GLEW>
        -DGLEW_CMAKE_TEST_TARGET_TYPE=$<TARGET_PROPERTY:GLEW::GLEW,TYPE>
        )

install(TARGETS ${target} DESTINATION bin)

set(PROJECT_NAME ${P_PROJECT_NAME})