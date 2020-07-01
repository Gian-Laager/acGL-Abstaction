cmake_minimum_required(VERSION 3.16)
project(basic_window)

set(CMAKE_CXX_STANDARD 17)

set(acGL_Abstraction_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/../..)
include(${acGL_Abstraction_ROOT_DIR}/CMakeLists.txt)
include_directories(${acGL_Abstraction_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} basic_window.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX _d)

message(STATUS "Linked ${target}")
target_link_libraries(${PROJECT_NAME} ${target})