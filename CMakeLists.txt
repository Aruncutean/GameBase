# CMakeList.txt : CMake project for test, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif ()

project("test")


set(FBX_SDK_PATH "C:\\Program Files\\Autodesk\\FBX\\FBX SDK\\2020.3.7")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(FBX_SDK_LIB_DIR "${FBX_SDK_PATH}/lib/x64/debug")
    message(STATUS "Using Debug library directory: ${FBX_SDK_LIB_DIR}")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(FBX_SDK_LIB_DIR  "${FBX_SDK_PATH}/lib/x64/release")
    message(STATUS "Using Release library directory: ${FBX_SDK_LIB_DIR}")
endif ()


include_directories(${CMAKE_SOURCE_DIR}/lib/glad/src/include)
include_directories(${CMAKE_SOURCE_DIR}/lib/SDL/include)
include_directories(${CMAKE_SOURCE_DIR}/lib/json/single_include/nlohmann)
include_directories(${CMAKE_SOURCE_DIR}/lib/glm)
include_directories(${CMAKE_SOURCE_DIR}/lib/stb)



link_directories(${CMAKE_SOURCE_DIR}/lib/SDL/lib/x64)

link_directories(${FBX_SDK_LIB_DIR})
include_directories(${FBX_SDK_PATH}/include)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE SRC_FILESH "${SRC_DIR}/*.h")

add_executable(test ${CMAKE_SOURCE_DIR}/lib/glad/src/glad.c
        ${SRC_FILES} ${SRC_FILESH})

set(FBX_SDK_LIBS
        libfbxsdk
        libxml2
        zlib
        alembic
)
add_definitions(-DFBXSDK_SHARED)

target_link_libraries(test SDL2main SDL2 opengl32 ${FBX_SDK_LIBS})

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET test PROPERTY CXX_STANDARD 20)
endif ()

