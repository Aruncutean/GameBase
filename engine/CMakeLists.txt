

set(FBX_SDK_PATH "C:\\Program Files\\Autodesk\\FBX\\FBX SDK\\2020.3.7")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(FBX_SDK_LIB_DIR "${FBX_SDK_PATH}/lib/x64/debug")
    message(STATUS "Using Debug library directory: ${FBX_SDK_LIB_DIR}")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(FBX_SDK_LIB_DIR  "${FBX_SDK_PATH}/lib/x64/release")
    message(STATUS "Using Release library directory: ${FBX_SDK_LIB_DIR}")
endif ()

include_directories(${PROJECT_SOURCE_DIR}/lib/glad/src/include)
include_directories(${PROJECT_SOURCE_DIR}/lib/SDL/include)
include_directories(${PROJECT_SOURCE_DIR}/lib/SDL_image/include)
include_directories(${PROJECT_SOURCE_DIR}/lib/glm)

link_directories(${PROJECT_SOURCE_DIR}/lib/SDL/lib/x64)
link_directories(${PROJECT_SOURCE_DIR}/lib/SDL_image/lib/x64)
link_directories(${FBX_SDK_LIB_DIR})

include_directories(${FBX_SDK_PATH}/include)
include_directories(${CMAKE_SOURCE_DIR}/include)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE SRC_FILESH "${SRC_DIR}/*.h")

set(FBX_SDK_LIBS
        libfbxsdk
        libxml2
        zlib
        alembic
)

add_definitions(-DFBXSDK_SHARED)


set(BASE_SOURCES
        ${PROJECT_SOURCE_DIR}/lib/glad/src/glad.c ${SRC_FILES} ${SRC_FILESH}
)

add_library(base_lib STATIC ${BASE_SOURCES})

#add_executable(test ${CMAKE_SOURCE_DIR}/lib/glad/src/glad.c ${SRC_FILES} ${SRC_FILESH}
#        ${GAME_FILES} ${GAME_FILESH}
#       )

target_link_libraries(test SDL2main SDL2 SDL2_image opengl32 ${FBX_SDK_LIBS})
