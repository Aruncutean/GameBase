cmake_minimum_required(VERSION 3.6)

project(MY_APP)

find_library(SDL2 SDL2)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/glad/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/glm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/stb)
add_library(main SHARED)

file(GLOB_RECURSE EXTERNAL_SRC ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../src/*.cpp)

target_sources(main PRIVATE ${EXTERNAL_SRC} ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c)

target_link_libraries(main SDL2)


